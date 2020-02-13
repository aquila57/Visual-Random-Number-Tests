/*
shwodds.c - Display the odds of a roll of dice  Version 0.1.0
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

void shwodds(int left, int right, xxfmt *xx)
   {
   int tot;
   double odds;
   double percent;
   char str[128];
   tot = left + right;
   if (tot < 2 || tot > 12)
      {
      fprintf(stderr,"Dice: Logic error 3\n");
      XCloseDisplay(xx->dpy);
      exit(1);
      } /* logic error 3 */
   switch(tot) {
      case 2:
	 odds = 1.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 3:
	 odds = 2.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 4:
	 odds = 3.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 5:
	 odds = 4.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 6:
	 odds = 5.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 7:
	 odds = 6.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 8:
	 odds = 5.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 9:
	 odds = 4.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 10:
	 odds = 3.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 11:
	 odds = 2.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      case 12:
	 odds = 1.0 / 36.0;
	 percent = (odds * 100.0);
	 sprintf(str,"Odds:    1 in %.1f", 1.0 / odds);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,120,str,strlen(str));
	 sprintf(str,"Percent: %4.1f", percent);
	 XDrawString(xx->dpy,xx->w,xx->gc,
	    20,140,str,strlen(str));
	 break;
      default:
         fprintf(stderr,"Dice: Logic error 4\n");
         XCloseDisplay(xx->dpy);
	 exit(1);
      } /* switch tot */
   } /* shwodds */
