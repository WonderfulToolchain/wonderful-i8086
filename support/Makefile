ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif
include wswan.mk

OBJDIR := obj
SRCDIRS := src
MKDIRS := $(OBJDIR)

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(OBJECTS)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(OBJECTS)

install: $(OBJECTS)
	install -d $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include
	install -d $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
	install -m 644 $(OBJDIR)/crt0.o $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
	install -m 644 wswan.ld.template $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
	install -m 644 wswan.mk $(WONDERFUL_TOOLCHAIN)/i8086
	install -m 755 bin2c.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-bin2c
	install -m 755 swanlink.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-swanlink
