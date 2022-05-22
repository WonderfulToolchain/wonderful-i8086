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

from pathlib import Path
import math
import os
import sys

executable_location = Path(sys.argv[0])
if executable_location.is_file():
	executable_location = executable_location.parent
executable_extension = ''
if os.name == 'nt':
	executable_extension = '.exe'

def align_up_to(i, alignment: int):
	if isinstance(i, int):
		return int(math.ceil(i / alignment) * alignment)
	else:
		append_bytes = align_up_to(len(i), alignment) - len(i)
		return i + (b'\x00' * append_bytes)

def power_of_two_up_to(i: int, min_size: int = None):
	if (min_size is not None) and (i < min_size):
		i = min_size
	i = int(2 ** math.ceil(math.log(i, 2)))
	return i