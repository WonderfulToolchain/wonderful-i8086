# wonderful-i8086

Experimental C toolchain for the WonderSwan. Early development.

## Rough build instructions

Only Linux supported. Use WSL2 on Windows. Tested on Arch Linux, YMMV.

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

## Known limitations

* Read-only data (const arrays, etc.) will only end up in ROM if declared as __far.
