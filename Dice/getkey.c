/*
getkey.c - Read keyboard with wait  Version 0.1.0
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

void getkey(xxfmt *xx)
   {
   /* after each race: wait for command or exposure */

   XSelectInput(xx->dpy, xx->w,
      KeyPressMask|ExposureMask|ButtonPressMask);

   xx->exposesw = 0;
   while(1)
      {
      int symbol;
      XEvent e;
      XKeyEvent *k;
      XButtonEvent *b;
      XNextEvent(xx->dpy, &e);
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         if (symbol == XK_Escape || symbol == XK_q)
            {
            xx->runflg = 0;
            break;
            } /* if quit */
	 else
            {
	    if (symbol == XK_Alt_L) continue;
            xx->runflg = 1;
            break;
            } /* if continue */
         } /* if keypress event */
      else if (e.type == ButtonPress)
         {
         b = (XButtonEvent *) &e;
	 if (b->button == 1)
	    {
	    break;
	    } /* if left button pressed */
	 else
	    {
	    xx->runflg = 0;
	    break;
	    } /* if right button pressed */
         } /* if keypress event */
      else if (e.type == Expose)
         {
         xx->exposesw = 1;
         break;
         } /* if expose event */
      } /* wait for window shutdown */
   } /* getkey */
