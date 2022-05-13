ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif
include $(WONDERFUL_TOOLCHAIN)/i8086/wswan.mk

TARGET := $(notdir $(shell pwd)).ws
OBJDIR := obj
RESDIR := res
SRCDIRS := src
MKDIRS := $(OBJDIR)
LIBS := -llzsa -lws -lc -lgcc
CFLAGS += -O2

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
EARLY_OBJECTS := $(OBJDIR)/image.o $(OBJDIR)/logo.o
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o) $(EARLY_OBJECTS)
CFLAGS += -I$(OBJDIR)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SWANLINK) -v -o $@ --output-elf $@.elf --linker-args $(LDFLAGS) $(WF_CRT0) $(OBJECTS) $(LIBS)

$(OBJDIR)/image.c: $(RESDIR)/image.png
	$(SUPERFAMICONV) tiles -i $< -M ws -p $(RESDIR)/image.pal.bin -d $(OBJDIR)/image.tiles.bin
	$(SUPERFAMICONV) map -i $< -M ws -p $(RESDIR)/image.pal.bin -t $(OBJDIR)/image.tiles.bin -d $(OBJDIR)/image.map.bin
	$(LZSA) -r -f 1 $(OBJDIR)/image.tiles.bin $(OBJDIR)/image.tiles.bin.lzsa1
	$(BIN2C) $@ $(RESDIR)/image.pal.bin:int16 $(OBJDIR)/image.tiles.bin.lzsa1 $(OBJDIR)/image.map.bin
	$(LZSA) -r -f 2 $(OBJDIR)/image.tiles.bin $(OBJDIR)/image.tiles.bin.lzsa2
	$(BIN2C) $@ $(RESDIR)/image.pal.bin:int16 $(OBJDIR)/image.tiles.bin.lzsa1 $(OBJDIR)/image.tiles.bin.lzsa2 $(OBJDIR)/image.map.bin

$(OBJDIR)/logo.c: $(RESDIR)/logo.png
	$(SUPERFAMICONV) tiles -i $< -M ws -D -F -p $(RESDIR)/image.pal.bin -d $(OBJDIR)/logo.tiles.bin
	$(BIN2C) $@ $(OBJDIR)/logo.tiles.bin

$(OBJDIR)/%.o: %.c $(EARLY_OBJECTS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(EARLY_OBJECTS) | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm -r $(OBJDIR)/*
	rm $(TARGET) $(TARGET).elf

-include $(DEPS)
