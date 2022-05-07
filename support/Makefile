include swan.mk

OBJDIR := obj
SRCDIRS := src
MKDIRS := $(OBJDIR)

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

all: $(OBJECTS)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	ia16-elf-gcc $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(OBJDIR)
	ia16-elf-as $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(OBJECTS)

install: $(OBJECTS)
	install -d $(TOOLCHAIN_PREFIX)/ws/include
	install -d $(TOOLCHAIN_PREFIX)/ws/lib
	install -m 644 $(OBJDIR)/crt0.o $(TOOLCHAIN_PREFIX)/ws/lib
	install -m 644 swan.ld.template $(TOOLCHAIN_PREFIX)/ws/lib
	install -m 644 swan.mk $(TOOLCHAIN_PREFIX)/ws/lib
	install -m 755 swanlink.py $(TOOLCHAIN_PREFIX)/bin/swanlink
