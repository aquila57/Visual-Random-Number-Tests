# etausgen.mak Version 0.1.0. Compile etausgen.c.
# Copyright (C) 2020   aquila57 at github.com

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

OBJ=etausgen.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-L. -letaus

etausgen:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o etausgen $(LDFLAGS)

etausgen.o:			etausgen.c
		$(CC) $(CFLAGS) etausgen.c

clean:
		rm -f $(OBJ) etausgen
