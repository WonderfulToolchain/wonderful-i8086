WONDERFUL_TARGET := wwitch

include $(WONDERFUL_TOOLCHAIN)/i8086/wonderful-i8086.mk

WF_LDSCRIPT := $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/wwitch.ld

WF_CRT0_ASC1 := $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_asc1.o
WF_CRT0_ASC2 := $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_asc2.o
WF_CRT0_JPN1 := $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_jpn1.o
WF_CRT0_JPN2 := $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_jpn2.o

CFLAGS += -mcmodel=small -mno-callee-assume-ss-data-segment

# Allow outputting Shift-JIS string literals.
CFLAGS += -fexec-charset=shift-jis
