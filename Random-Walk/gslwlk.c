/*
gslwlk.c - Random walk, GSL generators  Version 0.1.0
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
   rnd = gsl_rng_uniform(xx->rng);
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
   unsigned int dttk;          /* combined date and #ticks */
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /****************************************************/
   /* Initialize the seed to date/time/ticks           */
   /****************************************************/
   /* get clock ticks since boot                       */
   clk = times(&t);
   /* get date & time                                  */
   time(&now);
   /* combine date, time, and ticks into a single UINT */
   dttk = (unsigned int) (now ^ clk);
   /****************************************************/
   /* Initialize the random number generator           */
   /* in the GNU Scientific Library                    */
   /****************************************************/
   gsl_rng_env_setup();
   xx->rngtype = (gsl_rng_type *) gsl_rng_default;
   xx->rng = (gsl_rng *) gsl_rng_alloc(xx->rngtype);
   /* allocate GSL random number generator to set initial */
   /* values in the three fibonacci numbers               */
   gsl_rng_set(xx->rng, dttk);
   /******************************************************************/
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
   gsl_rng_free(xx->rng);
   free(xx);
   return(0);
   } /* main */
