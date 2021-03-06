/*
die3.c - Display die 3 of a roll of dice  Version 0.1.0
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

void die3(int left, xxfmt *xx)
   {
   int lean;
   if (!xx->exposesw)
      {
      if (left == LEFT)
	 xx->leftlean = etauspwr(xx->et,1);
      else
         xx->rghtlean = etauspwr(xx->et,1);
      } /* if not exposed */
   if (left == LEFT)
      lean = xx->leftlean;
   else
      lean = xx->rghtlean;
   if (lean)
      {
      XFillArc(xx->dpy,xx->w,xx->gc,
         left+05,25,15,15,0,CIRCLE);
      XFillArc(xx->dpy,xx->w,xx->gc,
         left+22,42,15,15,0,CIRCLE);
      XFillArc(xx->dpy,xx->w,xx->gc,
         left+40,60,15,15,0,CIRCLE);
      } /* if lean to right */
   else
      {
      XFillArc(xx->dpy,xx->w,xx->gc,
         left+05,60,15,15,0,CIRCLE);
      XFillArc(xx->dpy,xx->w,xx->gc,
         left+22,42,15,15,0,CIRCLE);
      XFillArc(xx->dpy,xx->w,xx->gc,
         left+40,25,15,15,0,CIRCLE);
      } /* if lean to left */
   } /* die3 */
