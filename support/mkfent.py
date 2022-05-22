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

# mkfent - WonderWitch file entry builder
#
# Supports the original .cf configuration format, as well as command line arguments.

from pathlib import Path
from types import SimpleNamespace   
from wfcommon import * 
import argparse
import codecs
import math
import os
import shutil
import struct
import subprocess
import sys
import tempfile
import traceback

# TODO: Add remaining modes
MODE_CHARS = {
	'x': 0x01, # execute
	'w': 0x02, # write
	'r': 0x04, # read
	'i': 0x20  # IL
}

def mode_to_int(m):
	try:
		return int(m, 0)
	except:
		mode = 0
		for i in m:
			if i in MODE_CHARS:
				mode |= MODE_CHARS[i]
			else:
				raise Exception(f"could not parse mode string: {m}")
		return mode

arg_parser = argparse.ArgumentParser(description='WonderWitch file entry builder for Wonderful')

# .cf arguments

arg_parser.add_argument('source', help='Input file', type=str)
arg_parser.add_argument('-o', dest='output', metavar='output.fx', help='Output file', type=str, default=None)
arg_parser.add_argument('--name', help='Entry name, up to 16 Shift-JIS characters', type=str, default=None)
arg_parser.add_argument('--info', help='Entry info, up to 24 Shift-JIS characters', type=str, default="")
arg_parser.add_argument('--mode', help='Entry mode', type=str, default='7')

# Wonderful-specific arguments

arg_parser.add_argument('-v', action='store_true', help='Enable verbose logging')
arg_parser.add_argument('--tools-path', metavar='PATH', type=str, help='Toolchain location', default=str(executable_location.parent.absolute()))

# Parse arguments, prepare globals.

def print_help_exit():
	arg_parser.print_help()
	sys.exit(1)

program_args = arg_parser.parse_args()
cf_args = program_args
cf_args_from_file = False

if Path(program_args.source).suffix == '.cf':
	cf_dict = {}
	for enc in ['utf-8', 'shift-jis']:
		try:
			with codecs.open(program_args.source, 'r', encoding=enc) as cf_file:
				for cf_line in cf_file:
					cf_kv = cf_line.split(":", maxsplit=1)
					if len(cf_kv) >= 2:
						cf_dict[cf_kv[0].strip()] = cf_kv[1].strip()
		except:
			print(f'Could not parse {Path(program_args.source).name} as {enc}, trying next encoding...', file=sys.stderr)
	cf_args = SimpleNamespace(**cf_dict)
	cf_args_from_file = True

def cf_has_arg(name):
	return getattr(cf_args, name, None) is not None

if (not cf_has_arg("source")) or (not Path(cf_args.source).exists()):
	if cf_args_from_file:
		raise Exception("Source file not found!")
	else:
		print_help_exit()

if (not cf_has_arg("output")):
	if cf_args_from_file:
		raise Exception("Output file not provided!")
	else:
		print_help_exit()


toolchain_prefix = Path(program_args.tools_path).absolute()
source_file_path = Path(cf_args.source).absolute()
input_bin_path = source_file_path
output_fent_path = Path(cf_args.output).absolute()
output_fent_name = getattr(cf_args, "name", output_fent_path.stem)
output_fent_info = getattr(cf_args, "info", output_fent_path)
output_fent_mode = mode_to_int(getattr(cf_args, "mode", "7"))

objcopy_path = toolchain_prefix / ("bin/ia16-elf-objcopy%s" % executable_extension)

def print_verbose(*args, **kwargs):
	if program_args.v:
		print(*args, **kwargs, file=sys.stderr)

temp_dir = None

def open_temp_dir():
	global temp_dir
	if temp_dir is None:
		temp_dir = tempfile.TemporaryDirectory()

def to_sjis_bytes(s, length_chars):
	b = s.encode('shift_jis')
	if len(b) > length_chars:
		raise Exception(f"string '{s}' too large: {len(b)} > {length_chars}")
	b += b'\x00' * (length_chars - len(b))
	return b

if input_bin_path.suffix == '.elf':
	open_temp_dir()

	input_elf_path = input_bin_path
	input_bin_path = Path(temp_dir.name) / "output.bin"

	print_verbose("Converting .elf to binary file")
	if not objcopy_path.exists():
		raise Exception("Cannot convert .elf file without objcopy!")
	objcopy_result = subprocess.run([str(objcopy_path), "-O", "binary", str(input_elf_path.absolute()), str(input_bin_path.absolute())])
	if objcopy_result.returncode != 0:
		raise Exception(f'objcopy exited with error code {objcopy_result.returncode}')

with open(input_bin_path, "rb") as f:
	input_bin_data = align_up_to(f.read(), 16)

input_resource_data = None

if cf_has_arg("resource"):
	input_resource_data = b''
	for res_path in cf_args.resource.split(" "):
		res_path = res_path.replace("\\", "/")
		with open(res_path, "rb") as f:
			input_resource_data += align_up_to(f.read(), 16)

# seconds since January 1st, 2000
output_fent_mtime = min(0x7FFFFFFF, max(0, int(round(source_file_path.lstat().st_mtime - 946080000))))

with open(output_fent_path, 'wb') as fent_file:
	file_length = len(input_bin_data)
	if input_resource_data is not None:
		file_length += len(input_resource_data)
	fent_file.write('#!ws'.encode("ascii"))
	fent_file.write(b'\xFF' * 60)
	fent_file.write(to_sjis_bytes(output_fent_name, 16))
	fent_file.write(to_sjis_bytes(output_fent_info, 24))
	fent_file.write(struct.pack("<IIHHIII",
		0x00000000, # file position?
		file_length, # file length, in bytes
		int((file_length + 127) >> 7), # file length, in XMODEM chunks
		output_fent_mode,
		output_fent_mtime,
		0x00000000, # TODO
		0xFFFFFFFF if input_resource_data is None else len(input_bin_data) # resources start
	))
	fent_file.write(input_bin_data)
	if input_resource_data is not None:
		fent_file.write(input_resource_data)
