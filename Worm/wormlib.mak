#  wormlib.mak - Compile worm library  Version 0.1.0
#  Copyright (C) 2020 aquila57 at github.com
# 
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:
# 
   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

OBJ=qinit.o \
	isrtq.o \
	rmq.o \
	initx.o \
	ifkey.o \
	getkey.o \
	etausinit.o \
	etausstrt.o \
	etaus.o \
	etausint.o \
	etauspwr.o \
	etausbit.o \
	etausunif.o \
	etausfrac.o \
	etausdspl.o \
	etausabt.o

CC=gcc

AR=ar

CFLAGS=-c -Wall -O2

LDFLAGS=

libworm.a:			$(OBJ)
		rm -f libworm.a
		$(AR) r libworm.a $(OBJ)

qinit.o:			qinit.c
		$(CC) $(CFLAGS) qinit.c

isrtq.o:			isrtq.c
		$(CC) $(CFLAGS) isrtq.c

rmq.o:				rmq.c
		$(CC) $(CFLAGS) rmq.c

initx.o:			initx.c
		$(CC) $(CFLAGS) initx.c

ifkey.o:			ifkey.c
		$(CC) $(CFLAGS) ifkey.c

getkey.o:			getkey.c
		$(CC) $(CFLAGS) getkey.c

etausinit.o:			etausinit.c
		$(CC) $(CFLAGS) etausinit.c

etausstrt.o:			etausstrt.c
		$(CC) $(CFLAGS) etausstrt.c

etaus.o:			etaus.c
		$(CC) $(CFLAGS) etaus.c

etausint.o:			etausint.c
		$(CC) $(CFLAGS) etausint.c

etauspwr.o:			etauspwr.c
		$(CC) $(CFLAGS) etauspwr.c

etausbit.o:			etausbit.c
		$(CC) $(CFLAGS) etausbit.c

etausunif.o:			etausunif.c
		$(CC) $(CFLAGS) etausunif.c

etausfrac.o:			etausfrac.c
		$(CC) $(CFLAGS) etausfrac.c

etausdspl.o:			etausdspl.c
		$(CC) $(CFLAGS) etausdspl.c

etausabt.o:			etausabt.c
		$(CC) $(CFLAGS) etausabt.c

clean:
		rm -f $(OBJ) libworm.a
