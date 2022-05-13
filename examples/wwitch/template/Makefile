ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif
include $(WONDERFUL_TOOLCHAIN)/i8086/wwitch.mk

TARGET := $(notdir $(shell pwd)).fx
TARGET_NAME := $(notdir $(shell pwd))
TARGET_INFO := $(TARGET_NAME)

OBJDIR := obj
SRCDIRS := src
MKDIRS := $(OBJDIR)
LIBS := -lww -lc
CFLAGS += -Os

#WF_CRT0 := $(WF_CRT0_ASC1)
#WF_CRT0 := $(WF_CRT0_ASC2)
#WF_CRT0 := $(WF_CRT0_JPN1)
WF_CRT0 := $(WF_CRT0_JPN2)

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@.elf -T$(WF_LDSCRIPT) $(LDFLAGS) $(WF_CRT0) $(OBJECTS) $(LIBS)
	$(MKFENT) -o $@ --name "$(TARGET_NAME)" --info "$(TARGET_INFO)" $@.elf

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	-$(RM) -r $(OBJDIR)/*
	-$(RM) $(TARGET) $(TARGET).elf

-include $(DEPS)
