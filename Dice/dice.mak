#!/usr/bin/make

# dice.mak Version 0.2.0. Compile dice.c.
# Copyright (C) 2004-2010 dondalah721@yahoo.com (Dondalah)

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

OBJ=dice.o

CC=gcc

CFLAGS=-c -Wall -O6 -I/usr/X11R6/include/X11

LDFLAGS=-L. -ldice -L/usr/X11R6/lib -lX11

dice:			$(OBJ) libdice.a
	$(CC) -Wall -O6 $(OBJ) -o dice $(LDFLAGS)

dice.o:			dice.c
	$(CC) $(CFLAGS) dice.c

clean:
	rm -f $(OBJ) dice
