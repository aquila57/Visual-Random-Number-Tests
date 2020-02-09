#!/usr/bin/make

# pxlrace.mak Version 1.1.0. Compile pxlrace.c.
# Copyright (C) 2001-2010 dondalah721@yahoo.com (Dondalah)

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to:

# 	Free Software Foundation, Inc.
# 	59 Temple Place - Suite 330
# 	Boston, MA  02111-1307, USA.

# Debian font
XFONT=\"8x16\"

# Slackware font
# XFONT=\"linux8x16\"

# uncomment if you want the pxlrace window in
# the upper left of your virtual desktop
# UPPERLEFT=-D UPPERLEFT

OBJ=pxlrace.o \
	initrnd.o \
	rnd.o \
	rndpwr.o \
	rndnum.o

CC=gcc

CFLAGS=-c -Wall -I/usr/X11R6/include/X11 \
        -DFONT=$(XFONT) \
	$(UPPERLEFT)

CFLG=-c -Wall

LDFLAGS=-L/usr/X11R6/lib -lX11

pxlrace:	$(OBJ)
	$(CC) -Wall $(OBJ) -o pxlrace $(LDFLAGS)

pxlrace.o:	pxlrace.c pxlrace.mak
	$(CC) $(CFLAGS) pxlrace.c

initrnd.o:	initrnd.c
	$(CC) $(CFLG) initrnd.c

rnd.o:		rnd.s
	$(CC) $(CFLG) rnd.s

rndpwr.o:	rndpwr.s
	$(CC) $(CFLG) rndpwr.s

rndnum.o:	rndnum.s
	$(CC) $(CFLG) rndnum.s

clean:
	rm -f pxlrace $(OBJ)
