CFLAGS := -ffunction-sections -march=v30mz -mtune=v30mz -mregparmcall -mcmodel=medium -msegelf -nostdlib -ffreestanding
CFLAGS += -isystem $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include
LDFLAGS := -L$(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
ASFLAGS := --32-segelf

CC := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-gcc
AR := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-ar
AS := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-as
LD := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-ld
NM := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-nm
OBJCOPY := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-objcopy
RANLIB := $(WONDERFUL_TOOLCHAIN)/i8086/bin/ia16-elf-ranlib
SUPERFAMICONV := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-superfamiconv
BIN2C := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-bin2c
LZSA := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-lzsa
SWANLINK := $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-swanlink

WS_CRT0 := $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib/crt0.o
