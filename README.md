# wonderful-i8086

Experimental C toolchain for the WonderSwan. Early development.

## Known limitations

* Read-only data (const arrays, etc.) will only end up in ROM if declared as `__far`.
    * To be more precise, by default, pointers are near pointers. In wonderful-i8086, this means they can only point to the console RAM. To point to SRAM or the console ROM, far pointers must be utilized.
* The WonderWitch target has compilation issues on non-trivial code, due to the necessary logic to handle DS ≠ SS. This is unlikely to be resolved shortly.
    * tkchia: "Yes, unfortunately support for %ss ≠ .data code is still extremely hacky and involves some not-quite-reliable deep black magic. (GCC was never quite designed in the first place to work with non-flat address spaces. Plus, the libgcc library was definitely not written with a %ss ≠ .data environment in mind.)" ([source](https://github.com/tkchia/gcc-ia16/issues/102))

## Installation instructions

Check back later.

## Licensing information

All source files have their licensing terms stated in the file itself. Crucially, for runtime components linked with a compiled binary, the licenses are as follows:

### Core libraries

* libgcc runtime library: [GPLv3 w/ Runtime Library Exception](https://www.fsf.org/news/2009-01-gcc-exception)
* startup/support code (`support/src/`): [zlib license](docs/COPYING.ZLIB)
* wonderful-i8086 C library (`libc/`): [CC0/public domain-like](docs/COPYING.CC0)
* wonderful-i8086 platform library (`libws/`, `libww/`): [zlib license](docs/COPYING.ZLIB)

### Additional libraries

* lzsa decompression library (`liblzsa/`): [zlib license](liblzsa/README.md)
