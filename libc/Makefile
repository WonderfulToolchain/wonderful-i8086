ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif

WONDERFUL_TARGET ?= wswan
include $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET).mk

OBJDIR := obj/$(WONDERFUL_TARGET)
TARGETDIR := build/$(WONDERFUL_TARGET)
TARGET := $(TARGETDIR)/libc.a
SRCDIRS := src src/ctype src/errno src/stdlib src/string
MKDIRS := $(OBJDIR) build/$(WONDERFUL_TARGET)
CFLAGS += -ffunction-sections

ifeq ($(WONDERFUL_TARGET), wwitch)
CFLAGS += -Os -DLIBC_LOCALE_SJIS
else
CFLAGS += -O2 -DLIBC_LOCALE_ASCII
endif

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

CFLAGS += -Iinclude

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(OBJDIR)
	$(AR) rcs $@ $(OBJECTS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	$(info $(foreach dir,$(MKDIRS),$(shell mkdir -p $(dir))))

clean:
	rm $(TARGET) $(OBJECTS)

install: $(TARGET)
	cp -r include/* $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/include/
	install -m 644 $(TARGET) $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/lib

-include $(DEPS)
