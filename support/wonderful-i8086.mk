CC := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-gcc
AR := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-ar
AS := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-as
LD := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-ld
NM := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-nm
OBJCOPY := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-objcopy
RANLIB := $(WONDERFUL_TOOLCHAIN)/toolchain/gcc-ia16-elf/bin/ia16-elf-ranlib
SUPERFAMICONV := $(WONDERFUL_TOOLCHAIN)/bin/wf-superfamiconv
BIN2C := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-bin2c
LZSA := $(WONDERFUL_TOOLCHAIN)/bin/wf-lzsa

# wswan target tools
FSBANKPACK := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-fsbankpack
SWANLINK := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-swanlink

# wwitch target tools
MKFENT := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-mkfent

CFLAGS := -ffunction-sections -march=v30mz -mtune=v30mz -mregparmcall -msegelf -nostdlib -ffreestanding
CFLAGS += -isystem $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/include
ASFLAGS := --32-segelf
LDFLAGS := -L$(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/lib

WF_CRT0 := $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/lib/crt0.o
