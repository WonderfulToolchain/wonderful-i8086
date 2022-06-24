ifndef WONDERFUL_TOOLCHAIN
$(error Please define WONDERFUL_TOOLCHAIN to point to the location of the Wonderful toolchain.)
endif
include wswan.mk

OBJDIR := obj
SRCDIRS := src
MKDIRS := $(OBJDIR)

OBJECTS := $(OBJDIR)/crt0.o \
	$(OBJDIR)/crt0_ww_asc1.o \
	$(OBJDIR)/crt0_ww_asc2.o \
	$(OBJDIR)/crt0_ww_jpn1.o \
	$(OBJDIR)/crt0_ww_jpn2.o

vpath %.c $(SRCDIRS)
vpath %.S $(SRCDIRS)

.PHONY: all clean install

all: $(OBJECTS)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.S $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/crt0_ww_asc1.o: crt0_ww.S $(OBJDIR)
	$(CC) $(CFLAGS) -DDISPLAY_MODE_ASCII1 -c -o $@ $<

$(OBJDIR)/crt0_ww_asc2.o: crt0_ww.S $(OBJDIR)
	$(CC) $(CFLAGS) -DDISPLAY_MODE_ASCII2 -c -o $@ $<

$(OBJDIR)/crt0_ww_jpn1.o: crt0_ww.S $(OBJDIR)
	$(CC) $(CFLAGS) -DDISPLAY_MODE_JAPANESE1 -c -o $@ $<

$(OBJDIR)/crt0_ww_jpn2.o: crt0_ww.S $(OBJDIR)
	$(CC) $(CFLAGS) -DDISPLAY_MODE_JAPANESE2 -c -o $@ $<

$(OBJDIR):
	$(info $(shell mkdir -p $(MKDIRS)))

clean:
	rm $(OBJECTS)

install: $(OBJECTS)
	install -d $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include
	install -d $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
	install -d $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/include
	install -d $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib
	install -m 644 $(OBJDIR)/crt0.o $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib/crt0.o
	install -m 644 $(OBJDIR)/crt0_ww_asc1.o $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_asc1.o
	install -m 644 $(OBJDIR)/crt0_ww_asc2.o $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_asc2.o
	install -m 644 $(OBJDIR)/crt0_ww_jpn1.o $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_jpn1.o
	install -m 644 $(OBJDIR)/crt0_ww_jpn2.o $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib/crt0_jpn2.o
	install -m 644 wswan.ld.template $(WONDERFUL_TOOLCHAIN)/i8086/wswan/lib
	install -m 644 wonderful-i8086.mk $(WONDERFUL_TOOLCHAIN)/i8086
	install -m 644 wswan.mk $(WONDERFUL_TOOLCHAIN)/i8086
	install -m 644 wwitch.mk $(WONDERFUL_TOOLCHAIN)/i8086
	install -m 644 wwitch.ld $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/lib
	install -m 755 bin2c.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-bin2c
	install -m 755 fsbankpack.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-fsbankpack
	install -m 755 mkfent.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-mkfent
	install -m 755 swanlink.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wf-swanlink
	install -m 755 wfcommon.py $(WONDERFUL_TOOLCHAIN)/i8086/bin/wfcommon.py
	install -m 644 src/wonderful-asm-wswan.h $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include/wonderful-asm.h
	install -m 644 src/wonderful-asm-wwitch.h $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/include/wonderful-asm.h
	install -m 644 src/wonderful-asm-common.h $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include
	install -m 644 src/wonderful-asm-common.h $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/include
	install -m 644 src/wonderful-wswan.h $(WONDERFUL_TOOLCHAIN)/i8086/wswan/include/wonderful.h
	install -m 644 src/wonderful-wwitch.h $(WONDERFUL_TOOLCHAIN)/i8086/wwitch/include/wonderful.h
