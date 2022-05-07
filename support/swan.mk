TOOLCHAIN_PREFIX ?= /opt/wonderful/i8086

CFLAGS := -Os -ffunction-sections -march=i80186 -mtune=v30 -mregparmcall -mcmodel=medium -ffreestanding -msegelf
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
SUPERFAMICONV := $(TOOLCHAIN_PREFIX)/bin/superfamiconv
SWANLINK := $(TOOLCHAIN_PREFIX)/bin/swanlink

WS_CRT0 := $(TOOLCHAIN_PREFIX)/ws/lib/crt0.o
