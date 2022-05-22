Using fsbankpack to create an in-memory asset filesystem {#fsbankpack}
===================================

Wonderful's default data mapping assumes that the linear ROM bank (0x40000 - 0xFFFFF) incorporates the executable binary's area,
leaving banks 0 and 1 (0x20000 - 0x3FFFF) for reading additional data. As 768KB can easily become restrictive for more expansive
game projects, a built-in filesystem creation tool called fsbackpack is provided.

## Using fsbankpack

    $(FSBANKPACK) -o filesystem.bin file1.bin file2.bin

will create two files:

 * `filesystem.bin`, containing the binary data;
 * `filesystem.h`, contains the following four defines:
   * `ASSET_FILE1_BIN` - the position of `file1.bin` in `filesystem.bin`,
   * `ASSET_FILE1_BIN_SIZE` - the length of `file1.bin` in bytes,
   * `ASSET_FILE2_BIN` - the position of `file2.bin` in `filesystem.bin`,
   * `ASSET_FILE2_BIN_SIZE` - the length of `file2.bin` in bytes.

Alternatively, instead of providing the filenames as command line arguments, one can create a file `filesystem.txt` with each file on a new line. Then, one can call fsbankpack as follows:

    $(FSBANKPACK) -o filesystem.bin -d filesystem.txt

One can also use fsbankpack in more advanced ways by incorporating filters:

 * `one_bank`: If you want to ensure `file1.bin` fits in one bank, you may use this filter: `file1.bin|one_bank`,
 * `bank_start`: If you want to ensure `file1.bin` starts at the beginning of a bank, you may use this filter: `file1.bin|bank_start`,
 * `alignX`: If you want to ensure `file1.bin` is aligned to a multiple of X, you may use this filter: `file1.bin|align256` will align it to a multiple of 256 bytes, for example.

## Accessing filesystem assets

Wonderful provides [utility functions](#CartridgeAsset) to easily convert asset positions into pointers usable in C code.