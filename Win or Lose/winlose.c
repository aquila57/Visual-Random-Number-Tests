/*
winlose.c Version 0.1.0. Pixel win lose status
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

int main(int argc, char **argv)
   {
   int i;
   int rslt;
   char str[256];
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx structure\n");
      exit(1);
      } /* out of memory */
   xx->et = (etfmt *) etausinit();
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
      winorlose(xx);
      if (xx->runflg)
	 {
	 getkey(xx);
         if (xx->repeat)
            {
            XClearWindow(xx->dpy,xx->w);
            } /* if rerun */
         } /* if still running */
      } /* for each race */
   XDestroyWindow(xx->dpy,xx->w);
   XCloseDisplay(xx->dpy);
   free(xx->et->state);
   free(xx->et);
   return(0);
   } /* main */
