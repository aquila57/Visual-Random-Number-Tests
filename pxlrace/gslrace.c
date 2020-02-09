/*
gslrace.c - Pixel Race, GSL generators  Version 0.1.0. 
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

#include "race.h"

void race(xxfmt *xx)
   {
   int i,tmpt,tmpw,holdt,holdw;
   int isrtsw;
   clock_t strtclk,clk;
   int dest,lane,dist,prevdist;
   int frstdist;
   char str[64];
   struct tms t;
   struct timespec req;         /* for nanosleep */
   struct timespec rem;         /* for nanosleep */
   req.tv_sec = rem.tv_sec = 0;
   req.tv_nsec = 1;
   rem.tv_nsec = 0;
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   dest = xx->dpywdth - 1;
   strtclk = times(&t);
   frstdist = 0;
   while (frstdist < dest)
      {
      double x;
      x = gsl_rng_uniform(xx->rng);     /* uniform number 0-1 */
      lane = (int) (x * xx->racers);
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
      ifkey(xx);
      if (!xx->runflg) return;
      nanosleep(&req,&rem);
      } /* for each step */
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
   } /* race */

int main(int argc, char **argv)
   {
   int i;
   int rslt;
   char str[256];
   unsigned int dttk;         /* combined date, time #ticks   */
   time_t now;                /* current date and time        */
   clock_t clk;               /* current number of ticks      */
   struct tms t;              /* structure used by times()    */
   xxfmt *xx;                 /* global structure             */
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /********************************************************************/
   gsl_rng_env_setup(); 
   xx->rngtype = (gsl_rng_type *) gsl_rng_default; 
   /* set RNG to GSL_RNG_TYPE */
   xx->rng = gsl_rng_alloc(xx->rngtype);
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL random number generator           */
   /* to date,time,#ticks                                  */
   gsl_rng_set(xx->rng, dttk);      /* initialize GSL seed   */
   /********************************************************************/
   initx(xx);
   xx->racers = xx->dpyhght - 30;
   if (argc > 2)
      {
      fprintf(stderr,"%s: Too many arguments\n", *argv);
      putstx(*argv, xx);
      } /* too many args */
   else if (argc == 2)
      {
      rslt = strcmp(*(argv+1), "-h");
      if (!rslt)
         {
         XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
         XSetForeground(xx->dpy, xx->gc, xx->blackColor);
         sprintf(str, "Usage: %s "\
	    "[number of racers]", *argv);
         XDrawImageString(xx->dpy,xx->w,xx->gc,
	    200,100,str,strlen(str));
         sprintf(str, "Where number of racers "
	    "is 2 - %3d", xx->racers);
         XDrawImageString(xx->dpy,xx->w,xx->gc,
	    200,140,str,strlen(str));
         sprintf(str, "Default is %3d", xx->racers);
         XDrawImageString(xx->dpy,xx->w,xx->gc,
	    200,180,str,strlen(str));
         sprintf(str, "Press <escape> to quit");
         XDrawImageString(xx->dpy,xx->w,xx->gc,
	    200,220,str,strlen(str));
	 xx->runflg = 1;
	 while (xx->runflg)
	    {
	    xx->runflg = 1;
	    getkey(xx);
	    } /* getkey escape */
	 putstx(*argv, xx);
	 } /* if help */
      i = atoi(*(argv+1));
      if (i < 2 || i > xx->racers)
         {
         fprintf(stderr,"%s: Invalid number " \
	    "of racers\n", *argv);
         putstx(*argv, xx);
	 } /* wrong # of racers */
      xx->racers = i;
      } /* one argument */
   xx->racer   = (int *) initracers(xx);
   xx->toptent = (int *) inittoptent();
   xx->toptenw = (int *) inittoptenw();
   XDrawPoint(xx->dpy,xx->w,xx->gc,100,0);
   xx->repeat = xx->runflg = 1;
   while (xx->repeat && xx->runflg)
      {
      xx->repeat = 0;
      initpxl(xx);
      race(xx);
      if (xx->runflg)
	 {
	 getkey(xx);
         if (xx->repeat)
            {
            XClearWindow(xx->dpy,xx->w);
            } /* if rerun */
         } /* if still running */
      } /* for each race */
   gsl_rng_free(xx->rng);
   XDestroyWindow(xx->dpy,xx->w);
   XCloseDisplay(xx->dpy);
   return(0);
   } /* main */
