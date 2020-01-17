#  libvis.mak - Compile visual test library Version 0.1.0
#  Copyright (C) 2020 aquila57 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

OBJ=getdie.o \
	bld_maxint.o \
	bld_rngtbl.o

CC=gcc

AR=ar

CFLAGS=-c -Wall -O2

LDFLAGS=

libvisual.a:			$(OBJ)
		rm -f libvisual.a
		$(AR) r libvisual.a $(OBJ)

getdie.o:			getdie.c
		$(CC) $(CFLAGS) getdie.c

bld_maxint.o:			bld_maxint.c
		$(CC) $(CFLAGS) bld_maxint.c

bld_rngtbl.o:			bld_rngtbl.c
		$(CC) $(CFLAGS) bld_rngtbl.c

clean:
		rm -f $(OBJ) libvisual.a
