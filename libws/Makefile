TOOLCHAIN_PREFIX := /opt/wonderful/i8086
include $(TOOLCHAIN_PREFIX)/ws/lib/swan.mk

OBJDIR := obj
SRCDIRS := src src/keypad src/system src/util
MKDIRS := $(OBJDIR)

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

CFLAGS += -Iinclude

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

all: libws.a

libws.a: $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm libws.a $(OBJECTS)

install:
	cp -r include/* $(TOOLCHAIN_PREFIX)/ws/include/
	install -m 644 libws.a $(TOOLCHAIN_PREFIX)/ws/lib
