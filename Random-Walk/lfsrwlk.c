/*
lfsrwlk.c - Random walk, LFSR generator  Version 0.1.0
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

#include "walk.h"

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* http://courses.cse.tamu.edu/walker/csce680/          */
/* lfsr_table.pdf                                       */
/* 64 bit LFSR is 64,63,61,60 with low order bit equal  */
/* to 64                                                */
/********************************************************/

#define MYLFSROUT (xx->out = (((xx->lfsr >> 4) \
   ^ (xx->lfsr >> 3) \
   ^ (xx->lfsr >> 1) \
   ^ (xx->lfsr >> 0)) & 1))

#define MYLFSRLOWBIT (xx->lowbit = xx->major & 1)

#define MYLFSRROLL (xx->major = xx->lfsr0 = \
(xx->major >> 1) | (xx->out << 31))

#define MYLFSRCARRY (xx->minor = xx->lfsr = \
(xx->minor >> 1) | (xx->lowbit << 31))

#define MYLFSR (MYLFSROUT,MYLFSRLOWBIT,MYLFSRROLL,MYLFSRCARRY)

void walk(xxfmt *xx)
   {
   int exx;
   int wyy;
   double rnd;
   int *p,*q,*r;
   exx = xx->dpywdth - 1;
   p = (int *) xx->line + xx->dpywdth - 2;
   q = (int *) xx->line;
   r = (int *) xx->line + xx->dpywdth - 1;
   while (p >= q)
      {
      if (*p != *r)
         {
	 int x;
	 int y;
	 x = exx - 1;
	 y = *p;
         XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
         XSetForeground(xx->dpy, xx->gc, xx->whiteColor);
	 XDrawPoint(xx->dpy,xx->w,xx->gc,x,y);
	 x++;
         XSetBackground(xx->dpy, xx->gc,xx->whiteColor);
         XSetForeground(xx->dpy, xx->gc,xx->blackColor);
	 XDrawPoint(xx->dpy,xx->w,xx->gc,x,y);
	 } /* if 2 pixels are different height */
      *r = *p;
      exx--;
      p--;
      r--;
      } /* for each pixel in line */
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->whiteColor);
   XDrawPoint(xx->dpy,xx->w,xx->gc,0,xx->line[0]);
   XSetForeground(xx->dpy, xx->gc, xx->blackColor);
   MYLFSR;
   rnd = (double) xx->lfsr / xx->modulus;
   if (rnd >= 0.5)
      {
      xx->line[0]--;
      if (xx->line[0] < 0) xx->line[0] = 0;
      XDrawPoint(xx->dpy,xx->w,xx->gc,0,xx->line[0]);
      } /* if higher on screen */
   else
      {
      xx->line[0]++;
      if (xx->line[0] >= xx->dpyhght) xx->line[0] = xx->dpyhght-1;
      XDrawPoint(xx->dpy,xx->w,xx->gc,0,xx->line[0]);
      } /* else lower on screen */
   wyy = xx->dpyhght >> 1;
   exx = xx->dpywdth;
   XSetForeground(xx->dpy,xx->gc, xx->red);
   XDrawLine(xx->dpy,xx->w,xx->gc,0,wyy,exx,wyy);
   } /* walk */

int main(void)
   {
   int *p,*q;
   int wyy;
   int exx;
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /*************************************/
   /* Initialize LFSR generator         */
   /*************************************/
   xx->et = (etfmt *) etausinit();
   xx->lfsr0 = xx->major  = etaus(xx->et);
   xx->lfsr  = xx->minor  = etaus(xx->et);
   xx->out   = xx->lowbit = 0;
   free(xx->et->state);
   free(xx->et);
   xx->modulus = 65536.0 * 65536.0;      /* 2^32 */
   /*************************************/
   initx(xx);
   wyy = xx->dpyhght >> 1;
   exx = xx->dpywdth;
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->red);
   XDrawLine(xx->dpy,xx->w,xx->gc,0,wyy,exx,wyy);
   p = (int *) xx->line + xx->dpywdth - 1;
   q = (int *) xx->line;
   while (p >= q) *p-- = wyy;
   xx->runflg = 1;
   while (xx->runflg)
      {
      walk(xx);
      ifkey(xx);
      } /* for each race */
   XDestroyWindow(xx->dpy,xx->w);
   XCloseDisplay(xx->dpy);
   free(xx);
   return(0);
   } /* main */
