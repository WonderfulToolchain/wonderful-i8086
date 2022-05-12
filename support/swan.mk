TOOLCHAIN_PREFIX ?= /opt/wonderful/i8086

CFLAGS := -ffunction-sections -march=v30mz -mtune=v30mz -mregparmcall -mcmodel=medium -ffreestanding -msegelf
CFLAGS += -isystem $(TOOLCHAIN_PREFIX)/ws/include
LDFLAGS := -L$(TOOLCHAIN_PREFIX)/ws/lib
ASFLAGS := --32-segelf

CC := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-gcc
AR := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-ar
AS := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-as
LD := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-ld
NM := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-nm
OBJCOPY := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-objcopy
RANLIB := $(TOOLCHAIN_PREFIX)/bin/ia16-elf-ranlib
SUPERFAMICONV := $(TOOLCHAIN_PREFIX)/bin/wf-superfamiconv
BIN2C := $(TOOLCHAIN_PREFIX)/bin/wf-bin2c
LZSA := $(TOOLCHAIN_PREFIX)/bin/wf-lzsa
SWANLINK := $(TOOLCHAIN_PREFIX)/bin/wf-swanlink

WS_CRT0 := $(TOOLCHAIN_PREFIX)/ws/lib/crt0.o
