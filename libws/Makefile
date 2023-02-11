ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif

WONDERFUL_TARGET ?= wswan
include $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET).mk

OBJDIR := obj/$(WONDERFUL_TARGET)
TARGETDIR := build/$(WONDERFUL_TARGET)
TARGET := $(TARGETDIR)/libws.a
SRCDIRS := src src/cartridge src/display src/dma src/eeprom src/keypad src/rtc src/serial src/system src/util
MKDIRS := $(OBJDIR) build/$(WONDERFUL_TARGET)
CFLAGS += -O2 -ffunction-sections

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

CFLAGS += -Iinclude

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean doc install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(TARGET) $(OBJECTS)

doc:
	@ mkdir -p build/doc
	doxygen

install: $(TARGET)
	cp -r include/* $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/include/
	install -m 644 $(TARGET) $(WONDERFUL_TOOLCHAIN)/i8086/$(WONDERFUL_TARGET)/lib

-include $(DEPS)
