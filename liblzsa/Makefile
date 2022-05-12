ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif
include $(WONDERFUL_TOOLCHAIN)/i8086/wswan.mk

OBJDIR := obj
MKDIRS := $(OBJDIR)
CFLAGS += -O2

SOURCES_SMALL := decompress_small_v1.S decompress_small_v2.S
OBJECTS_SMALL := $(SOURCES_SMALL:%.S=$(OBJDIR)/%.o)

SOURCES_FAST := decompress_speed_v1.S decompress_speed_v2.S
OBJECTS_FAST := $(SOURCES_FAST:%.S=$(OBJDIR)/%.o)

DEPS := $(OBJECTS_SMALL:.o=.d) $(OBJECTS_FAST:.o=.d)
CFLAGS += -MMD -MP

CFLAGS += -Iinclude

vpath %.c src
vpath %.S src

all: liblzsa_small.a liblzsa.a

liblzsa_small.a: $(OBJECTS_SMALL)
	$(AR) rcs $@ $(OBJECTS_SMALL)

liblzsa.a: $(OBJECTS_FAST)
	$(AR) rcs $@ $(OBJECTS_FAST)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(TARGET) $(OBJECTS_SMALL) $(OBJECTS_FAST)

install:
	cp -r include/* $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include/
	install -m 644 liblzsa_small.a $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
	install -m 644 liblzsa.a $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib

-include $(DEPS)
