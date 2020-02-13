/*
dice.c Version 0.1.0. Roll a pair of dice
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

int main(int argc, char **argv)
   {
   int i,j;
   int rslt1,rslt2;
   int oddsw,logsw;
   int hndl;
   int bgcolor;
   char fname[256];
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx structure\n");
      exit(1);
      } /* out of memory */
   i = j = xx->exposesw = oddsw = logsw = 0;
   hndl = 0;
   xx->scrw = SCRW;
   xx->scrh = SCRH - 60;
   xx->altbg = 0;
   if (argc > 4) putstx(*argv);
   if (argc > 1)
      {
      i = 1;
      while (i < argc)
	 {
	 rslt1 = strcmp(*(argv+i),"-o");
	 rslt2 = strcmp(*(argv+i),"-f");
	 if (!rslt1)
	    {
	    oddsw = 1;
	    xx->scrh = SCRH;
	    } /* if odds calculation */
	 else if (!rslt2)
	    {
	    logsw = 1;
	    i = i + 1;
	    strcpy(fname,*(argv+i));
	    hndl = opn(fname);
	    } /* if logging file */
	 else
	    {
	    fprintf(stderr,"dice: invalid parm %s\n",
	       *(argv+i));
	    putstx(*argv);
	    exit(1);
	    } /* bad parm */
	 i++;
	 } /* for each parm */
      } /* if parm present */
   xx->et = (etfmt *) etausinit();
   initx(xx->scrw, xx->scrh, xx);
   setclr(xx);
   if (etaus(xx->et) >> 31)
      bgcolor = xx->maroon;
   else
      bgcolor = xx->navy;
   xx->runflg = 1;
   while (xx->runflg)
      {
      if (xx->exposesw)
	 {
         XSetBackground(xx->dpy, xx->gc, bgcolor);
	 XSetForeground(xx->dpy, xx->gc, bgcolor);
         XFillRectangle(xx->dpy,xx->w,xx->gc,
	    0,0,xx->scrw,xx->scrh);
         XSetForeground(xx->dpy, xx->gc, xx->ivory);
	 } /* if exposed */
      if (xx->altbg)
         {
         bgcolor = xx->maroon;
         XSetBackground(xx->dpy, xx->gc, bgcolor);
         XSetForeground(xx->dpy, xx->gc, bgcolor);
         XFillRectangle(xx->dpy,xx->w,xx->gc,
            0,0,xx->scrw,xx->scrh);
         XSetForeground(xx->dpy, xx->gc, xx->ivory);
         } /* if maroon background */
      else
         {
         bgcolor = xx->navy;
         XSetBackground(xx->dpy, xx->gc, bgcolor);
         XSetForeground(xx->dpy, xx->gc, bgcolor);
         XFillRectangle(xx->dpy,xx->w,xx->gc,
            0,0,xx->scrw,xx->scrh);
         XSetForeground(xx->dpy, xx->gc, xx->ivory);
         xx->exposesw = 0;
         } /* if navy background */
      xx->altbg = (xx->altbg ^ 1) & 1;
      XSetForeground(xx->dpy, xx->gc, xx->ivory);
      XFillRectangle(xx->dpy,xx->w,xx->gc,
         LEFT,20,60,60);
      XFillRectangle(xx->dpy,xx->w,xx->gc,
         RIGHT,20,60,60);
      XSetForeground(xx->dpy, xx->gc, xx->blackColor);
      if (!xx->exposesw)
	 {
	 // do {
            // i = etauspwr(xx->et,3) + 1;
	    // } while (i > 6);
	 while (1)
	    {
	    i = etauspwr(xx->et, 3) + 1;
	    if (i < 7) break;
	    } /* infinite loop until die is 1-6 */
	 } /* if not exposed */
      switch(i) {
         case 1:
	    die1(LEFT,xx);
	    break;
         case 2:
	    die2(LEFT,xx);
	    break;
         case 3:
	    die3(LEFT,xx);
	    break;
         case 4:
	    die4(LEFT,xx);
	    break;
         case 5:
	    die5(LEFT,xx);
	    break;
         case 6:
	    die6(LEFT,xx);
	    break;
         default:
            fprintf(stderr,"Dice: Logic error 1\n");
	    exit(1);
         } /* switch i */
      if (!xx->exposesw)
	 {
	 // do {
            // j = etauspwr(xx->et,3) + 1;
	    // } while (j > 6);
	 while (1)
	    {
	    j = etauspwr(xx->et, 3) + 1;
	    if (j < 7) break;
	    } /* infinite loop until die is 1-6 */
	 } /* if not exposed */
      switch(j) {
         case 1:
	    die1(RIGHT,xx);
	    break;
         case 2:
	    die2(RIGHT,xx);
	    break;
         case 3:
	    die3(RIGHT,xx);
	    break;
         case 4:
	    die4(RIGHT,xx);
	    break;
         case 5:
	    die5(RIGHT,xx);
	    break;
         case 6:
	    die6(RIGHT,xx);
	    break;
         default:
            fprintf(stderr,"Dice: Logic error 2\n");
	    exit(1);
         } /* switch j */
      if (oddsw)
	 {
	 /* the switch has already been toggled */
         XSetBackground(xx->dpy, xx->gc, bgcolor);
         XSetForeground(xx->dpy, xx->gc, bgcolor);
         XFillRectangle(xx->dpy, xx->w, xx->gc,
	    20, 100, 160, 40);
         XSetForeground(xx->dpy, xx->gc, xx->ivory);
	 shwodds(i,j,xx);
	 } /* if show odds */
      if (!xx->exposesw)
	 {
	 if (logsw) wrtlog(i,j,hndl,xx);
	 } /* if not exposed */
      xx->exposesw = 0;
      getkey(xx);
      } /* for each roll */
   XDestroyWindow(xx->dpy,xx->w);
   XCloseDisplay(xx->dpy);
   if (logsw) cls(hndl);
   free(xx->et->state);
   free(xx->et);
   return(0);
   } /* main */
