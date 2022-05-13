# wonderful-i8086

Experimental C toolchain for the WonderSwan. Early development.

## Known limitations

* Read-only data (const arrays, etc.) will only end up in ROM if declared as `__far`.
    * To be more precise, by default, pointers are near pointers. In wonderful-i8086, this means they can only point to the console RAM. To point to SRAM or the console ROM, far pointers must be utilized.

## Rough build instructions

Only Linux is officially supported at this time. Using WSL2 on Windows is recommended. The scripts have been tested on Arch Linux.

### Base toolchain

    $ export WONDERFUL_TOOLCHAIN=/opt/wonderful
    # create directory
    $ mkdir -p "$WONDERFUL_TOOLCHAIN"/i8086
    # build tools
    $ cd toolchain
    $ ./fetch.sh
    $ ./build.sh all
    # build base support
    $ cd ../support
    $ make install

### WonderSwan target (WIP)

    # build libc
    $ cd ../libc
    $ make install
    # build libws
    $ cd ../libws
    $ make install
    # build liblzsa
    $ cd ../liblzsa
    $ make install

### WonderWitch target (WIP)

    # build libc
    $ cd ../libc
    $ make WONDERFUL_TARGET=wwitch install
    # build libww
    $ cd ../libww
    $ make install

## Licensing information

All source files have their licensing terms stated in the file itself. Crucially, for runtime components linked with a compiled binary, the licenses are as follows:

### Core libraries

* libgcc runtime library: [GPLv3 w/ Runtime Library Exception](https://www.fsf.org/news/2009-01-gcc-exception)
* startup/support code (`support/src/`): [zlib license](docs/COPYING.ZLIB)
* wonderful-i8086 C library (`libc/`): [CC0/public domain-like](docs/COPYING.CC0)
* wonderful-i8086 platform library (`libws/`, `libww/`): [zlib license](docs/COPYING.ZLIB)

### Additional libraries

* lzsa decompression library (`liblzsa/`): [zlib license](liblzsa/README.md)
