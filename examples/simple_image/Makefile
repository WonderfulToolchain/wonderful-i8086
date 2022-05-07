TOOLCHAIN_PREFIX := /opt/wonderful/i8086
include $(TOOLCHAIN_PREFIX)/ws/lib/swan.mk

TARGET := $(notdir $(shell pwd)).ws
OBJDIR := obj
RESDIR := res
SRCDIRS := src
MKDIRS := $(OBJDIR)
LIBS := -lws -lc

CSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES := $(foreach dir,$(SRCDIRS),$(notdir $(wildcard $(dir)/*.S)))
EARLY_OBJECTS := $(OBJDIR)/image.o
OBJECTS := $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.S=$(OBJDIR)/%.o) $(EARLY_OBJECTS)
CFLAGS += -I$(OBJDIR)

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SWANLINK) -v -o $@ --output-elf $@.elf --linker-args $(LDFLAGS) $(WS_CRT0) $(OBJECTS) $(LIBS)

$(OBJDIR)/image.c: $(RESDIR)/image.png
	$(SUPERFAMICONV) palette -i $< -M ws -P 1 -d $(OBJDIR)/image.pal.bin
	$(SUPERFAMICONV) tiles -i $< -M ws -p $(OBJDIR)/image.pal.bin -d $(OBJDIR)/image.tiles.bin
	$(SUPERFAMICONV) map -i $< -M ws -p $(OBJDIR)/image.pal.bin -t $(OBJDIR)/image.tiles.bin -d $(OBJDIR)/image.map.bin
	$(BIN2C) $@ $(OBJDIR)/image.tiles.bin $(OBJDIR)/image.map.bin

$(OBJDIR)/%.o: %.c $(OBJDIR) $(EARLY_OBJECTS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(OBJDIR) $(EARLY_OBJECTS)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(TARGET) $(OBJECTS) $(OBJDIR)/*.bin $(OBJDIR)/image.c
