WONDERFUL_TARGET := wswan

include $(WONDERFUL_TOOLCHAIN)/i8086/wonderful-i8086.mk

CFLAGS += -mcmodel=medium
