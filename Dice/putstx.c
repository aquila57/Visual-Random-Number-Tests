/*
putstx.c - Display dice syntax  Version 0.1.0
Copyright (C) 2020  aquila57 at github.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to:

	Free Software Foundation, Inc.
	59 Temple Place - Suite 330
	Boston, MA  02111-1307, USA.
*/

#include "dice.h"

void putstx(pgm)
char *pgm;
   {
   fprintf(stderr,"Usage: %s [-o] "
      "[-f filename]\n", pgm);
   fprintf(stderr,"Where -o means \"show "
      "the odds\"\n");
   fprintf(stderr,"      -f filename is "
      "the log file name\n");
   fprintf(stderr,"Click on the left mouse "
      "button to re-roll the dice.\n");
   fprintf(stderr,"Click on the right mouse "
      "button to quit.\n");
   fprintf(stderr,"Or press 'q' to quit\n");
   fprintf(stderr,"Press any other key to "
      "re-roll the dice.\n");
   exit(1);
   } /* putstx */
