# Makefile for hexedit

PRODUCT = hexedit
VERSION = 1.2.13

SHELL = /bin/sh
CROSS_COMPILE =/home/cwp/lede-M26/staging_dir/toolchain-mips_24kc_gcc-5.4.0_musl/bin/
export STAGING_DIR=/home/cwp/lede-M26/staging_dir/toolchain-mips_24kc_gcc-5.4.0_musl/
CC = $(CROSS_COMPILE)mips-openwrt-linux-gcc
CFLAGS = -g -O2
CPPFLAGS = 

LDFLAGS = 
LIBS =  -lncurses
DEFS = -DHAVE_CONFIG_H
INSTALL = /usr/bin/install -c

# Installation directories
prefix = /usr/local
exec_prefix = ${prefix}
mandir = ${prefix}/share/man
bindir = ${exec_prefix}/bin

INCL = hexedit.h
SRCS = hexedit.c display.c mark.c page.c file.c interact.c misc.c search.c
OBJS = $(SRCS:.c=.o)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(DEFS) $(CFLAGS) $(CPPFLAGS) -c $<

all: $(PRODUCT)

$(PRODUCT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -rf *~ *.o core *.cache config.status config.log $(PRODUCT)

distclean: clean
	rm -f Makefile config.h

install: $(PRODUCT)
	$(INSTALL) -d -m 755 $(DESTDIR)$(bindir)
	$(INSTALL) -s -m 755 $(PRODUCT) $(DESTDIR)$(bindir)
	$(INSTALL) -d -m 755 $(DESTDIR)$(mandir)/man1
	$(INSTALL) -m 644 $(PRODUCT).1 $(DESTDIR)$(mandir)/man1
