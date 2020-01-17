#!/usr/bin/make

# fibodots.mak Version 1.0.0. Compile fibodots.c.
# Copyright (C) 2016   aquila62 at github.com

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

OBJ=fibodots.o

CC=gcc

CFLAGS=-c -Wall -O2 -I/usr/X11R6/include/X11

LDFLAGS=-L. -leegl -L/usr/X11R6/lib -lX11

fibodots:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o fibodots $(LDFLAGS)

fibodots.o:			fibodots.c
		$(CC) $(CFLAGS) fibodots.c

clean:
		rm -f $(OBJ) fibodots