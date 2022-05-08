# wonderful-i8086

Experimental C toolchain for the WonderSwan. Early development.

## Known limitations

* Read-only data (const arrays, etc.) will only end up in ROM if declared as __far.

## Rough build instructions

Only Linux is officially supported at this time. Using WSL2 on Windows is recommended. The scripts have been tested on Arch Linux.

    # create directory
    $ mkdir -p /opt/wonderful/i8086
    # build tools
    $ cd toolchain
    $ ./fetch.sh
    $ ./build.sh all
    # build base support
    $ cd ../support
    $ make install
    # build libc
    $ cd ../libc
    $ make install
    # build libws
    $ cd ../libws
    $ make install

## Licensing information

All source files have their licensing terms stated in the file itself. Crucially, for runtime components linked with a compiled binary, the licenses are as follows:

* libgcc runtime library: [GPLv3 w/ Runtime Library Exception](https://www.fsf.org/news/2009-01-gcc-exception)
* `support/src/crt0.S`: [zlib license](docs/COPYING.ZLIB)
* `libc/`: [CC0/public domain-like](docs/COPYING.CC0)
* `libws/`: [zlib license](docs/COPYING.ZLIB)
