TOOLCHAIN_PREFIX := /opt/wonderful/i8086
include $(TOOLCHAIN_PREFIX)/ws/lib/swan.mk

TARGET := $(notdir $(shell pwd)).ws
OBJDIR := obj
SRCDIRS := src
MKDIRS := $(OBJDIR)
LIBS := -lws -lc

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SWANLINK) -v -o $@ --output-elf $@.elf --linker-args $(LDFLAGS) $(WS_CRT0) $(OBJECTS) $(LIBS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(TARGET) $(OBJECTS)

-include $(DEPS)
