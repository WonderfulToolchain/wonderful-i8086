ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif
include $(WONDERFUL_TOOLCHAIN)/i8086/wswan.mk

TARGET := $(notdir $(shell pwd)).ws
OBJDIR := obj
RESDIR := res
SRCDIRS := src
MKDIRS := $(OBJDIR)
LIBS := -lws -lc -lgcc
CFLAGS += -O0

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
EARLY_OBJECTS := $(OBJDIR)/assets.o
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o) $(EARLY_OBJECTS)
CFLAGS += -I$(OBJDIR)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SWANLINK) -v -o $@ --output-elf $@.elf --linker-args $(LDFLAGS) $(WS_CRT0) $(OBJECTS) $(LIBS)

$(OBJDIR)/%.o: %.c $(EARLY_OBJECTS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(EARLY_OBJECTS) | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR)/assets.c: $(RESDIR)/game_tiles.png $(RESDIR)/game_bg.png $(RESDIR)/palette.bin
	$(SUPERFAMICONV) tiles -i $(RESDIR)/game_tiles.png -M ws -p $(RESDIR)/palette.bin -d $(OBJDIR)/game_tiles.tiles.bin
	$(SUPERFAMICONV) tiles -i $(RESDIR)/game_bg.png -M ws -p $(RESDIR)/palette.bin -d $(OBJDIR)/game_bg.tiles.bin
	$(SUPERFAMICONV) map -i $(RESDIR)/game_bg.png -M ws -p $(RESDIR)/palette.bin -t $(OBJDIR)/game_bg.tiles.bin -d $(OBJDIR)/game_bg.map.bin
	$(BIN2C) $@ $(OBJDIR)/game_tiles.tiles.bin $(OBJDIR)/game_bg.tiles.bin $(OBJDIR)/game_bg.map.bin

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm -r $(OBJDIR)/*
	rm $(TARGET) $(TARGET).elf

-include $(DEPS)
