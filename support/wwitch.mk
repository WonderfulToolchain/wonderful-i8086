WONDERFUL_TARGET := wwitch

include $(WONDERFUL_TOOLCHAIN)/i8086/wonderful-i8086.mk

CFLAGS += -mcmodel=small -mno-callee-assume-ss-data-segment
