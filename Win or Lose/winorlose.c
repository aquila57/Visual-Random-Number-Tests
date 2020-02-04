/*
winorlose.c - Calculate win lose status  Version 0.1.0
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

#include "winlose.h"

void winorlose(xxfmt *xx)
   {
   int cycle;
   int i,tmpt,tmpw,holdt,holdw;
   int isrtsw;
   int half;
   clock_t strtclk,clk;
   int lane,dist,prevdist;
   int frstdist;
   char str[64];
   struct tms t;
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   strtclk = times(&t);
   half = xx->dpywdth >> 1;
   dist = frstdist = half;
   cycle = 4096;
   while (cycle--)
      {
      for (lane = 0;lane < xx->racers;lane++)
         {
	 int rslt;
	 while (1)
	    {
	    rslt = etauspwr(xx->et,2);
	    if (rslt != 3) break;
	    } /* 3 way flip */
	 if (!rslt)
	    {
	    dist = ++xx->racer[lane];
            if (dist > 1)
               {
               prevdist = dist - 2;
               XSetForeground(xx->dpy, xx->gc, xx->whiteColor);
               XDrawPoint(xx->dpy,xx->w,xx->gc,
	          prevdist,lane+25);
               } /* if room to clear */
            XSetForeground(xx->dpy, xx->gc, xx->blackColor);
            XDrawPoint(xx->dpy,xx->w,xx->gc,
	       dist,lane+25);
	    } /* if advance */
	 else if (rslt == 1)
	    {
	    dist = --xx->racer[lane];
            if (dist > 1)
               {
               prevdist = dist + 2;
               XSetForeground(xx->dpy, xx->gc, xx->whiteColor);
               XDrawPoint(xx->dpy,xx->w,xx->gc,
	          prevdist,lane+25);
               } /* if room to clear */
            XSetForeground(xx->dpy, xx->gc, xx->blackColor);
            XDrawPoint(xx->dpy,xx->w,xx->gc,
	       dist,lane+25);
	    } /* if advance */
         if (dist > frstdist)
            {
            frstdist = dist;
            xx->first = lane;
            /* because of exposure */
            XDrawImageString(xx->dpy,xx->w,xx->gc,
	       220,16,"Leader = ",9);
            sprintf(str, "%3d", xx->first+1);
            XDrawImageString(xx->dpy,xx->w,xx->gc,
	       300,16,str,4);
            XDrawImageString(xx->dpy,xx->w,xx->gc,
	       340,16," of ",4);
            sprintf(str, "%3d", xx->racers);
            XDrawImageString(xx->dpy,xx->w,xx->gc,
	       375,16,str,4);
            } /* if new leader */
	 } /* for each racer */
      } /* for each step */
   fprintf(stderr,"winorlose: firstdist %d "
      "frst %d\n", frstdist, xx->first);
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->red);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist,xx->first+25);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist-1,xx->first+25);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist-2,xx->first+25);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist,xx->first+24);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist-1,xx->first+24);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist-2,xx->first+24);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist,xx->first+26);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist-1,xx->first+26);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      frstdist-2,xx->first+26);
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->blackColor);
   clk = times(&t);
   xx->winticks = clk - strtclk;
   i = 0;
   while (i < 10)
      {
      isrtsw = 0;
      if (xx->winticks < xx->toptent[i])
         isrtsw = 1;
      else if (xx->winticks == xx->toptent[i]
         && xx->first < xx->toptenw[i])
         isrtsw = 1;
      if (isrtsw)
         {
         tmpt = xx->toptent[i];
         tmpw = xx->toptenw[i];
         xx->toptent[i] = xx->winticks;
         xx->toptenw[i++] = xx->first;
         while (i < 10)
            {
            holdt = xx->toptent[i];
            xx->toptent[i] = tmpt;
            tmpt = holdt;
            holdw = xx->toptenw[i];
            xx->toptenw[i++] = tmpw;
            tmpw = holdw;
            } /* shift right */
         } /* insert here */
      else i++;
      } /* insert winner */
   shwwinner(xx);
   } /* winorlose */

