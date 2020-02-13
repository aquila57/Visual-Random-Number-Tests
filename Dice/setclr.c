/*
dice.c - Roll a pair of dice  Version 0.1.0
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

void setclr(xxfmt *xx)
   {
   int rslt;

   rslt = XAllocNamedColor(xx->dpy,xx->cmap,"maroon",
      &xx->scrdef,&xx->exctdef);

   if (rslt < 0)
      {
      fprintf(stderr,"XAllocNamedColor failed\n");
      perror("XAllocNamedColor failed");
      exit(1);
      } /* if error */
   xx->maroon = xx->scrdef.pixel;

   rslt = XAllocNamedColor(xx->dpy,xx->cmap,"navy",
      &xx->scrdef,&xx->exctdef);

   if (rslt < 0)
      {
      fprintf(stderr,"XAllocNamedColor failed\n");
      perror("XAllocNamedColor failed");
      exit(1);
      } /* if error */
   xx->navy = xx->scrdef.pixel;

   rslt = XAllocNamedColor(xx->dpy,xx->cmap,"ivory",
      &xx->scrdef,&xx->exctdef);

   if (rslt < 0)
      {
      fprintf(stderr,"XAllocNamedColor failed\n");
      perror("XAllocNamedColor failed");
      exit(1);
      } /* if error */
   xx->ivory = xx->scrdef.pixel;

   } /* setclr */
