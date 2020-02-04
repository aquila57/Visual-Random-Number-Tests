# winloselib.mak - Compile libwinlose.a  Version 0.1.0
# Copyright (C) 2020  aquila57 at github.com

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

OBJ=etausabt.o \
	etausbit.o \
	etaus.o \
	etausdspl.o \
	etausfrac.o \
	etausinit.o \
	etausint.o \
	etauspwr.o \
	etausstrt.o \
	etausunif.o \
	getkey.o \
	ifkey.o \
	initpxl.o \
	initracers.o \
	inittoptent.o \
	inittoptenw.o \
	initx.o \
	putstx.o \
	redraw.o \
	shwwinner.o \
	winorlose.o

CC=gcc

CFLAGS=-c -Wall -O2 -I/usr/X11R6/include/X11

LDFLAGS=-L/usr/X11R6/lib -lX11

libwinlose.a:		$(OBJ)
		rm -f libwinlose.a
		ar r libwinlose.a $(OBJ)

etausabt.o:		etausabt.c
	$(CC) $(CFLAGS) etausabt.c

etausbit.o:		etausbit.c
	$(CC) $(CFLAGS) etausbit.c

etaus.o:		etaus.c
	$(CC) $(CFLAGS) etaus.c

etausdspl.o:		etausdspl.c
	$(CC) $(CFLAGS) etausdspl.c

etausfrac.o:		etausfrac.c
	$(CC) $(CFLAGS) etausfrac.c

etausinit.o:		etausinit.c
	$(CC) $(CFLAGS) etausinit.c

etausint.o:		etausint.c
	$(CC) $(CFLAGS) etausint.c

etauspwr.o:		etauspwr.c
	$(CC) $(CFLAGS) etauspwr.c

etausstrt.o:		etausstrt.c
	$(CC) $(CFLAGS) etausstrt.c

etausunif.o:		etausunif.c
	$(CC) $(CFLAGS) etausunif.c

getkey.o:		getkey.c
	$(CC) $(CFLAGS) getkey.c

ifkey.o:		ifkey.c
	$(CC) $(CFLAGS) ifkey.c

initpxl.o:		initpxl.c
	$(CC) $(CFLAGS) initpxl.c

initracers.o:		initracers.c
	$(CC) $(CFLAGS) initracers.c

inittoptent.o:		inittoptent.c
	$(CC) $(CFLAGS) inittoptent.c

inittoptenw.o:		inittoptenw.c
	$(CC) $(CFLAGS) inittoptenw.c

initx.o:		initx.c
	$(CC) $(CFLAGS) initx.c

putstx.o:		putstx.c
	$(CC) $(CFLAGS) putstx.c

redraw.o:		redraw.c
	$(CC) $(CFLAGS) redraw.c

shwwinner.o:		shwwinner.c
	$(CC) $(CFLAGS) shwwinner.c

winorlose.o:		winorlose.c
	$(CC) $(CFLAGS) winorlose.c

clean:
	rm -f $(OBJ) libwinlose.a 
