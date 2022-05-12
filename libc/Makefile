TOOLCHAIN_PREFIX := /opt/wonderful/i8086
include $(TOOLCHAIN_PREFIX)/ws/lib/swan.mk

TARGET := libc.a
OBJDIR := obj
SRCDIRS := src src/stdlib src/string
MKDIRS := $(OBJDIR)
CFLAGS += -O2

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

$(TARGET): $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(TARGET) $(OBJECTS)

install:
	cp -r include/* $(TOOLCHAIN_PREFIX)/ws/include/
	install -m 644 $(TARGET) $(TOOLCHAIN_PREFIX)/ws/lib

-include $(DEPS)
