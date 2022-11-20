#!/usr/bin/env python3
#
# Copyright (c) 2022 Adrian "asie" Siekierka
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# swanlink - WonderSwan ROM linker for Wonderful
#
# This code is a massive hack. I'm sorry.
# The rough goal is to arrange the code at the *top* of the ROM, with the
# bottom being available for virtual filesystems, etc. This is opposite to
# the typical arrangement.

from pathlib import Path
from wfcommon import * 
import argparse
import math
import os
import shutil
import struct
import subprocess
import sys
import tempfile

MAX_BIN_BANKS = 12 # could be 14 or 15 with special crt0 configuration
MAX_BANKS = 256
HEADER_SIZE = 16
BANK_COUNT_TO_ROM_SIZE = {
	2: 0x01,
	4: 0x01,
	8: 0x02,
	16: 0x03,
	32: 0x04,
	48: 0x05,
	64: 0x06,
	96: 0x07,
	128: 0x08,
	256: 0x09
}

SRAM_TYPES = {
	"NONE": 0x00,
	"SRAM_8KB": 0x01,
	"SRAM_32KB": 0x02,
	"SRAM_128KB": 0x03,
	"SRAM_256KB": 0x04,
	"SRAM_512KB": 0x05,
	"EEPROM_128B": 0x10,
	"EEPROM_2KB": 0x20,
	"EEPROM_1KB": 0x50
}

# Define arguments.

def publisher_id_type(arg):
	try:
		i = int(arg)
	except ValueError:
		raise argparse.ArgumentTypeError("must be an integer")
	if i < 0 or i > 255:
		raise argparse.ArgumentTypeError("must be between 0 and 255")
	return i

def game_id_type(arg):
	try:
		i = int(arg)
	except ValueError:
		raise argparse.ArgumentTypeError("must be an integer")
	if i < 0 or i > 99:
		raise argparse.ArgumentTypeError("must be between 0 and 99")
	return i

def game_version_type(arg):
	try:
		i = int(arg)
	except ValueError:
		raise argparse.ArgumentTypeError("must be an integer")
	if i < 0 or i > 127:
		raise argparse.ArgumentTypeError("must be between 0 and 127")
	return i

def banks_type(arg):
	try:
		i = int(arg)
	except ValueError:
		raise argparse.ArgumentTypeError("must be an integer")
	if i < 2 or i > MAX_BANKS:
		raise argparse.ArgumentTypeError(f"must be between 2 and {MAX_BANKS}")
	if power_of_two_up_to(i) != i:
		raise argparse.ArgumentTypeError("must be a power of two")
	return i

arg_parser = argparse.ArgumentParser(description='WonderSwan ROM linker for Wonderful')
arg_parser.add_argument('-o', metavar='output.ws', help='Output ROM file', type=str, required=True)
arg_parser.add_argument('-a', action='append', metavar='[b0:]file.bin', type=str, help='Attach file. Optionally, specify bank (bX) or raw position (X)')
arg_parser.add_argument('-v', action='store_true', help='Enable verbose logging')
arg_parser.add_argument('--output-elf', metavar='out.elf', help='Output ELF file', type=str)
arg_parser.add_argument('--tools-path', metavar='PATH', type=str, help='Toolchain location', default=str(executable_location.parent.absolute()))
arg_parser.add_argument('--color', action='store_true', help='Mark ROM as WSC-compatible')
arg_parser.add_argument('--ram-type', metavar='RAM_TYPE', type=str, help='RAM used. Available values: %s' % ", ".join(SRAM_TYPES.keys()), default="NONE")
arg_parser.add_argument('--rom-size', metavar='BANKS', type=banks_type, help='ROM size, in 64K banks')
arg_parser.add_argument('--rom-speed', metavar='SPEED', type=int, help='ROM access speed, 1 or 3 cycles', default=1)
arg_parser.add_argument('--rom-bus-size', metavar='SIZE', type=int, help='ROM bus size, 8 or 16 bits', default=16)
arg_parser.add_argument('--orientation', metavar='ORIENT', type=str, help='Default orientation, "horizontal" (default) or "vertical"', default="horizontal")
arg_parser.add_argument('--rtc', action="store_true", help='ROM uses RTC')
arg_parser.add_argument('--unlock-ieep', action="store_true", help='ROM can write to internal EEPROM')
arg_parser.add_argument('--disable-custom-bootsplash', action="store_true", help='ROM disables custom console boot splash')
arg_parser.add_argument('--publisher-id', metavar='ID', type=publisher_id_type, help='Publisher ID, 0-255', default=255)
arg_parser.add_argument('--game-id', metavar='ID', type=game_id_type, help='Game ID, 0-99', default=0)
arg_parser.add_argument('--game-version', metavar='VER', type=game_version_type, help='Game version, 0-127', default=1)
arg_parser.add_argument('--load-offset', metavar='OFFSET', type=lambda x: int(x, 0), help='Linked code load offset')
arg_parser.add_argument('--ld-template', metavar='PATH', type=str, help='Linker template', default=None)
arg_parser.add_argument('--linker-args', action="store_true", required=True, help='ld linker args follow after this argument')
arg_parser.add_argument('--rom-empty-fill', metavar='VALUE', type=lambda x: int(x, 0), help='ROM empty fill value, 0xFF by default', default=0xFF)
# FIXME: Needs more linkscript/crt0 patches...
# arg_parser.add_argument('--heap-start', metavar='ADDR', type=lambda x: int(x, 0), help='Link-side heap start address', default=0x0000)
arg_parser.add_argument('--heap-length', metavar='LEN', type=lambda x: int(x, 0), help='Link-side heap length', default=0x2000)

try:
	linker_args_split = sys.argv.index("--linker-args")
except:
	arg_parser.print_help(file=sys.stderr)
	exit(1)

# Parse arguments, prepare globals.

linker_args = sys.argv[linker_args_split+1:]
program_args = arg_parser.parse_args(sys.argv[1:linker_args_split+1])

toolchain_prefix = Path(program_args.tools_path).absolute()
output_rom_path = Path(program_args.o).absolute()
output_elf_path = None
if program_args.output_elf:
	output_elf_path = Path(program_args.output_elf).absolute()

ld_template_path = toolchain_prefix / 'wswan/lib/wswan.ld.template'
if program_args.ld_template is not None:
	ld_template_path = Path(ld_template).absolute()
ld_path = toolchain_prefix / ("../toolchain/gcc-ia16-elf/bin/ia16-elf-ld%s" % executable_extension)
objcopy_path = toolchain_prefix / ("../toolchain/gcc-ia16-elf/bin/ia16-elf-objcopy%s" % executable_extension)
size_path = toolchain_prefix / ("../toolchain/gcc-ia16-elf/bin/ia16-elf-size%s" % executable_extension)

rom_layout = {}

def print_verbose(*args, **kwargs):
	if program_args.v:
		print(*args, **kwargs, file=sys.stderr)

def get_rom_layout_size():
	global rom_layout
	if len(rom_layout) <= 0:
		return 0
	else:
		last_key = max(rom_layout.keys())
		return last_key + len(rom_layout[last_key])

def add_to_rom_layout(position: int, data, data_name: str = None):
	global rom_layout
	if isinstance(data, Path):
		if data_name is None:
			data_name = data.name
		with open(data, "rb") as f:
			data = f.read()
	if data_name is None:
		data_name = "data"
	if position is None:
		position = get_rom_layout_size()
	position_end = position + len(data) - 1
	for r_start in rom_layout.keys():
		r_end = r_start + len(rom_layout[r_start]) - 1
		if ((position >= r_start) and (position <= r_end)) or ((position_end >= r_start) and (position_end <= r_end)):
			raise Exception(f"Range overlap for addition at offset {position}, size {len(data)}")
	print_verbose("Laying out '%s' at 0x%X, size %d bytes" % (data_name, position, len(data)))
	rom_layout[position] = data

def call_linker(temp_dir: Path, template_file: Path, output_elf: Path, output_file: Path, rom_offset: int, rom_banks: int, args: list[str]):
	template_out_file = temp_dir / 'link.ld'
	with open(template_out_file, 'w') as outf:
		rom_bank_offset = (256 - rom_banks)
		result = subprocess.run(["sed",
			"-e", f"s/%ROM_AREA_START%/{rom_offset}/g",
			"-e", f"s/%ROM_BANK_OFFSET%/{rom_bank_offset}/g",
			"-e", f"s/%RAM_HEAP_START%/0x00000/g",
			"-e", f"s/%RAM_HEAP_LENGTH%/{program_args.heap_length}/g",
			str(template_file.absolute())], stdout=outf)
		if result.returncode != 0:
			raise Exception(f'sed exited with error code {result.returncode}')
	ld_args = [str(ld_path), "-T", str(template_out_file), "-o", str(output_elf.absolute())]
	ld_args.extend(args)
	result = subprocess.run(ld_args)
	if result.returncode != 0:
		raise Exception(f'ld exited with error code {result.returncode}')
	objcopy_result = subprocess.run([str(objcopy_path), "-O", "binary", str(output_elf.absolute()), str(output_file.absolute())])
	if objcopy_result.returncode != 0:
		raise Exception(f'objcopy exited with error code {objcopy_result.returncode}')

def byte_to_bcd(i: int) -> int:
	return (int(i / 10) << 4) | int(i % 10)

# Append files from -a arguments to ROM.

if program_args.a is not None:
	for entry in program_args.a:
		entry = entry.split(":", maxsplit=1)
		if len(entry) >= 2:
			if entry[0].startswith("b"):
				entry_pos = int(entry[0][1:], 0) * 0x10000
			else:
				entry_pos = int(entry[0], 0)
			entry_name = entry[1]
		else:
			entry_pos = get_rom_layout_size()
			entry_name = entry[0]
		add_to_rom_layout(entry_pos, Path(entry_name))

# Link.

def calc_rom_size(final_rom_offset: int):
	if program_args.rom_size:
		rom_size = program_args.rom_size * 0x10000
	else:
		rom_size = get_rom_layout_size() + (0x100000 - final_rom_offset)
	return power_of_two_up_to(rom_size, 131072)

with tempfile.TemporaryDirectory() as temp_dir:
	temp_path = Path(str(temp_dir)).absolute()
	final_rom_offset = program_args.load_offset
	if final_rom_offset is None:
		# Step 1: Create ELF.
		temporary_elf = temp_path / "stage1.elf"
		temporary_bin = temp_path / "stage1.bin"
		call_linker(temp_path, ld_template_path, temporary_elf, temporary_bin, 0x40000, 2, linker_args)
		# Step 2: Measure ELF size, rounded up to 0x10.
		bin_size = align_up_to(temporary_bin.stat().st_size, 0x10)
		# Use the measured ELF size to calculate the minimum ROM size.
		# Use that to calculate the new ELF location.
		final_rom_offset = 0x100000 - HEADER_SIZE - bin_size
		print_verbose("Program size is %d bytes, load at %04X:0000" % (bin_size, final_rom_offset >> 4))
	rom_size = calc_rom_size(final_rom_offset)
	# Step 3: Create ELF and BIN at final ROM location.
	target_elf = output_elf_path or (temp_path / "stage2.elf")
	target_bin = temp_path / "stage2.bin"
	call_linker(temp_path, ld_template_path, target_elf, target_bin, final_rom_offset, rom_size >> 16, linker_args)
	# Step 4: Build ROM.
	# The final five bytes of the BIN file have to go to FFFF:0000.
	# Step 4a: Import BIN file.
	with open(target_bin, "rb") as f:
		bin_data = f.read()
	bin_data = align_up_to(bin_data, 16)
	bin_size = len(bin_data)
	if (bin_size + HEADER_SIZE) > (MAX_BIN_BANKS * 0x10000):
		raise Exception(f"bin too large: {bin_size} bytes > {MAX_BIN_BANKS} banks")
	if (final_rom_offset + bin_size) > 0xFFFF0:
		raise Exception("out of bounds: load address %04X:0000 + %d > 0xFFFF0" % (final_rom_offset >> 4, bin_size))
	rom_size = calc_rom_size(final_rom_offset)
	if rom_size > (MAX_BANKS * 0x10000):
		raise Exception(f"rom too large: {rom_size} bytes > {MAX_BANKS} banks")
	print_verbose("ROM size is %d bytes" % (rom_size))
	final_rom_position = rom_size - (0x100000 - final_rom_offset)
	add_to_rom_layout(final_rom_position, bin_data, data_name='bin')
	# Step 4b: Create header.
	hdr_maintenance = 0x00
	hdr_publisher = program_args.publisher_id
	hdr_color = 0x01 if program_args.color else 0x00
	hdr_game_id = byte_to_bcd(program_args.game_id)
	hdr_game_version = program_args.game_version
	if program_args.unlock_ieep:
		hdr_game_version |= (1 << 7)
	if program_args.disable_custom_bootsplash:
		hdr_maintenance |= (1 << 7)
	hdr_rom_size = BANK_COUNT_TO_ROM_SIZE[rom_size >> 16]
	hdr_save_type = 0x00
	if program_args.ram_type:
		if program_args.ram_type in SRAM_TYPES:
			hdr_save_type = SRAM_TYPES[program_args.ram_type]
		else:
			hdr_save_type = int(program_args.ram_type, 0)
	hdr_flags = 0x0000
	if program_args.rtc:
		hdr_flags |= (1 << 8)
	if program_args.rom_speed == 1:
		hdr_flags |= (1 << 2)
	if program_args.rom_bus_size == 8:
		hdr_flags |= (1 << 1)
	if program_args.orientation == 'vertical':
		hdr_flags |= (1 << 0)
	bin_call_routine = struct.pack("<BHH", 0xEA, 0x0000, final_rom_offset >> 4)
	rom_header = bin_call_routine + struct.pack("<BBBBBBBHH",
		hdr_maintenance, hdr_publisher, hdr_color, hdr_game_id,
		hdr_game_version, hdr_rom_size, hdr_save_type, hdr_flags, 0x0000)
	add_to_rom_layout(rom_size - 0x10, rom_header, data_name='header')
	# Step 4c: Output ROM, calculate checksum in the process.
	hdr_checksum = 0x0000
	print_verbose('Saving as %s' % output_rom_path.name)
	with open(output_rom_path, 'wb') as rom_file:
		rom_file.write(struct.pack("<B", program_args.rom_empty_fill) * rom_size)
		for position in rom_layout.keys():
			data = rom_layout[position]
			rom_file.seek(position, 0)
			rom_file.write(data)
			hdr_checksum += sum(data)
		rom_file.seek(rom_size - 2)
		rom_file.write(struct.pack("<H", hdr_checksum & 0xFFFF))
