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
CFLAGS += -Os

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o)
CFLAGS += -I$(OBJDIR)

DEPS := $(OBJECTS:.o=.d)
CFLAGS += -MMD -MP

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS) $(OBJDIR)/fs.bin
	$(SWANLINK) -v -o $@ -a $(OBJDIR)/fs.bin --output-elf $@.elf --linker-args $(LDFLAGS) $(WF_CRT0) $(OBJECTS) $(LIBS)

$(OBJDIR)/fs.bin: $(OBJDIR)/image.tiles.bin.lzsa2 $(OBJDIR)/image.map.bin $(OBJDIR)/logo.tiles.bin
	$(FSBANKPACK) -v -o $@ $^

$(OBJDIR)/image.tiles.bin.lzsa2: $(RESDIR)/image.png | $(OBJDIR)
	$(SUPERFAMICONV) tiles -i $< -M ws -p $(RESDIR)/image.pal.bin -d $(OBJDIR)/image.tiles.bin
	$(SUPERFAMICONV) map -i $< -M ws -p $(RESDIR)/image.pal.bin -t $(OBJDIR)/image.tiles.bin -d $(OBJDIR)/image.map.bin
	$(LZSA) -r -f 2 $(OBJDIR)/image.tiles.bin $(OBJDIR)/image.tiles.bin.lzsa2

$(OBJDIR)/logo.tiles.bin: $(RESDIR)/logo.png | $(OBJDIR)
	$(SUPERFAMICONV) tiles -i $< -M ws -D -F -p $(RESDIR)/image.pal.bin -d $(OBJDIR)/logo.tiles.bin

$(OBJDIR)/%.o: %.c $(OBJDIR)/fs.bin | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(OBJDIR)/fs.bin | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm -r $(OBJDIR)/*
	rm $(TARGET) $(TARGET).elf

-include $(DEPS)
