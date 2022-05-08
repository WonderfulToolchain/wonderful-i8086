TOOLCHAIN_PREFIX := /opt/wonderful/i8086
include $(TOOLCHAIN_PREFIX)/ws/lib/swan.mk

OBJDIR := obj
MKDIRS := $(OBJDIR)

SOURCES_SMALL := decompress_small_v1.S decompress_small_v2.S
OBJECTS_SMALL := $(SOURCES_SMALL:%.S=$(OBJDIR)/%.o)

SOURCES_FAST := decompress_speed_v1.S decompress_speed_v2.S
OBJECTS_FAST := $(SOURCES_FAST:%.S=$(OBJDIR)/%.o)

DEPS := $(OBJECTS_SMALL:.o=.d) $(OBJECTS_FAST:.o=.d)
CFLAGS += -MMD -MP

CFLAGS += -Iinclude

vpath %.c src
vpath %.S src

all: liblzma_small.a liblzma.a

liblzma_small.a: $(OBJECTS_SMALL)
	$(AR) rcs $@ $(OBJECTS_SMALL)

liblzma.a: $(OBJECTS_FAST)
	$(AR) rcs $@ $(OBJECTS_FAST)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(TARGET) $(OBJECTS_SMALL) $(OBJECTS_FAST)

install:
	cp -r include/* $(TOOLCHAIN_PREFIX)/ws/include/
	install -m 644 liblzma_small.a $(TOOLCHAIN_PREFIX)/ws/lib
	install -m 644 liblzma.a $(TOOLCHAIN_PREFIX)/ws/lib

-include $(DEPS)
