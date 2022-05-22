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

from datetime import datetime
from pathlib import Path
from wfcommon import * 
import argparse
import os
import re
import sys
import traceback

# File allocation rules:
#
# - zero_aligned: must start at position 0 in a bank
# - one_bank: must fit within one bank
class File:
	def __init__(self, name: str, data):
		self.name = name
		self.data = data
		self.position = 0
		self.length = len(data)
		self.zero_aligned = False
		self.one_bank = False

	def place_at(self, pos):
		self.position = pos

	def header_prefix(self):
		aname = re.sub("[^0-9A-Z]", "_", Path(self.name).name.upper())
		return f"ASSET_{aname}"

MIN_ALIGNMENT = 16
BANK_SIZE = 65536
BANK_END = (BANK_SIZE * 256)
files = []

def file_pairs(files):
	for i in range(0, len(files)):
		if (i + 1) >= len(files):
			yield (files[i], None)
		else:
			yield (files[i], files[i + 1])

def file_empty_spots(files):
	if len(files) <= 0:
		yield (0, BANK_END)
		return
	for i in file_pairs(files):
		if i[1] is None:
			yield (i[0].position + i[0].length, BANK_END)
		else:
			yield (i[0].position + i[0].length, i[1].position)

def append_file(f: File):
	global files
	for s in file_empty_spots(files):
		s_pos, s_end = s
		s_len = s_end - s_pos
		if (f.zero_aligned) or (f.one_bank and (int(s_pos / BANK_SIZE) != int(s_end / BANK_SIZE))):
			s_pos = align_up_to(s_pos, BANK_SIZE)
			s_len = s_end - s_pos
		if s_len >= f.length:
			f.place_at(s_pos)
			files.append(f)
			files = list(sorted(files, key=lambda x: x.position))
			return
	raise Exception(f"Could not allocate space for {f.name}")

arg_parser = argparse.ArgumentParser(description='File bank packing tool for Wonderful')

arg_parser.add_argument('source', help='Input files', type=str, nargs='+')
arg_parser.add_argument('-d', action='store_true', help='Use definition file as a list of input files')
arg_parser.add_argument('-H', dest='header', metavar='output.h', help='Output header file', type=str, default=None)
arg_parser.add_argument('-o', dest='output', metavar='output.bin', help='Output file', type=str, required=True)
arg_parser.add_argument('-v', action='store_true', help='Enable verbose logging')
arg_parser.add_argument('--tools-path', metavar='PATH', type=str, help='Toolchain location', default=str(executable_location.parent.absolute()))

# Parse arguments, prepare globals.

program_args = arg_parser.parse_args()

def print_help_exit():
	arg_parser.print_help()
	sys.exit(1)

def print_verbose(*args, **kwargs):
	if program_args.v:
		print(*args, **kwargs, file=sys.stderr)

toolchain_prefix = Path(program_args.tools_path).absolute()
output_file_path = Path(program_args.output).absolute()
if program_args.header is not None:
	header_file_path = Path(program_args.header).absolute()
else:
	header_file_path = Path(program_args.output).with_suffix(".h").absolute()

# Parse file list

file_list = program_args.source
if program_args.d:
	if len(file_list) != 1:
		raise Exception("Must specify only one file to use definition mode!")
	with open(file_list[0], "r") as f:
		file_list = []
		for line in f:
			file_list.append(f)

files_to_add = []

for fstr in file_list:
	fstr = fstr.strip().split("|")
	fname = fstr[0]
	with open(fname, "rb") as ff:
		fdata = ff.read()
	f = File(fname, align_up_to(fdata, MIN_ALIGNMENT))
	for ffilter in fstr[1:]:
		if ffilter.startswith("align"):
			f.data = align_up_to(f.data, int(ffilter[5:], 0))
		elif ffilter.startswith("one_bank"):
			f.one_bank = True
		elif ffilter.startswith("bank_start"):
			f.zero_aligned = True
	files_to_add.append(f)

# Allocate files

def add_files(flt):
	global files_to_add
	for i in list(filter(flt, files_to_add)):
		append_file(i)
		files_to_add.remove(i)

add_files(lambda x: x.zero_aligned)
add_files(lambda x: x.one_bank)
add_files(lambda x: True)

if len(files_to_add) > 0:
	raise Exception("Did not add all files!")

# Generate binary file

with open(output_file_path, 'wb') as rom_file:
	for f in files:
		rom_file.seek(f.position, 0)
		rom_file.write(f.data)

# Generate header file

with open(header_file_path, 'w') as header_file:
	current_date_str = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

	header_file.write(f"// autogenerated by fsbankpack on {current_date_str}\n")
	header_file.write("#pragma once\n")
	header_file.write("#include <stdint.h>\n")
	for f in files:
		header_file.write("\n")
		header_file.write(f"#define {f.header_prefix()} {f.position}\n")
		header_file.write(f"#define {f.header_prefix()}_SIZE {f.length}\n")