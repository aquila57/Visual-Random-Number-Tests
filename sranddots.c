/*
sranddots.c Version 0.1.0. Paint random dots on an X Windows screen
Copyright (C) 2020   aquila57 at github.com

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

/* This program is a random bitmap in X Windows */
/* Let the program run at least 15 seconds to see the */
/* bitmap fill up with random data. */
/* Press 'q' to quit */
/* Cover up the window with another screen */
/* Then uncover the bitmap screen to see it fill up */
/* with data again */

/* This program runs the subrand random number generator,    */
/* created by Professor Donald E. Knuth at Stanford University.  */
/* subrand is a subtractive generator.                       */
/* state[n] = state[n-1] - state[n-2]                        */
/* if (state[n] < 0) state[n] += MOD                         */
/* where MOD is 10^9                                         */
/* The subrand generator here has been taken from            */
/* http://rosettacode.org/wiki/Subtractive_generator#C       */

#define MOD (1000000000)

/* to define the escape key */
#define XK_MISCELLANY 1
#define XK_LATIN1 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <assert.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

/* structure for X Windows meta-data */
typedef struct xxstruct {
   int whiteColor,blackColor;
   int rootwh;      /* root window height */
   int rootww;      /* root window width  */
   int dpyhght;     /* display window height */
   int dpywdth;     /* display window width  */
   int repeat;
   int runflg;
   eefmt *ee;
   int state[55];
   int si;
   int sj;
   int first_seed;
   double subrand_mod;
   double count;
   unsigned long red;
   Display *dpy;
   Window w;
   GC gc;
   Font fontid;
   Screen *dfltscr;
   Colormap cmap;
   XColor scrdef,exctdef;
   } xxfmt;

/* X Windows code is based on: */
/* http://tronche.com/gui/x/xlib-tutorial/2nd-program-anatomy.html */
/* or */
/* http://tronche.com/gui/x  */

/* wait until key pressed */
void getkey(xxfmt *xx)
   {
   /* after each pause wait for command or exposure */

   XSelectInput(xx->dpy, xx->w,
      KeyPressMask|ExposureMask);

   while(1)
      {
      int symbol;
      XEvent e;
      XKeyEvent *k;
      XNextEvent(xx->dpy, &e);
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         xx->repeat = 0;
         if (symbol == XK_Escape || symbol == 'q')
            {
            xx->repeat = 0;
	    xx->runflg = 0;
            break;
            } /* if quit */
         else if (symbol == 'r' || symbol == 'n')
            {
            xx->repeat = 1;
            break;
            } /* if next */
         } /* if keypress event */
      else if (e.type == Expose)
         {
	 XClearWindow(xx->dpy,xx->w);
         continue;
         } /* if expose event */
      } /* wait for window shutdown */
   } /* getkey */

/* test keyboard for input character */
void ifkey(xxfmt *xx)
   {
   int msk;
   int symbol;
   int XCheckMaskEvent();
   XEvent e;
   XKeyEvent *k;

   msk = KeyPressMask|ExposureMask;

   XSelectInput(xx->dpy, xx->w, msk);

   while (XCheckMaskEvent(xx->dpy, msk, &e))
      {
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         if (symbol == XK_Escape
	    || symbol == XK_q)
            {
            xx->runflg = 0;
            } /* if quit */
         } /* if keypress event */
      else if (e.type == Expose)
         {
	 XClearWindow(xx->dpy,xx->w);
         } /* if expose event */
      } /* if event received */
   } /* ifkey */

/* initialize X Windows */
void initx(xxfmt *xx)
   {
   int rslt;
   char title[64];

   xx->dpy = XOpenDisplay(NULL);

   if (xx->dpy == NULL)
      {
      fprintf(stderr,"X Windows failure\n");
      exit(1);
      } /* if X Windows is not active */

   assert(xx->dpy);

   /* get dimensions of root window */
   xx->rootww = XDisplayWidth(xx->dpy,0);
   xx->rootwh = XDisplayHeight(xx->dpy,0);

   /* make display window smaller than root window */
   /* allow for menu bar on top */
   // xx->dpywdth = xx->rootww -  80;
   // xx->dpyhght = xx->rootwh - 100;
   xx->dpywdth = 512;        /* need a power of 2 */
   xx->dpyhght = 512;        /* need a power of 2 */

   xx->whiteColor = WhitePixel(xx->dpy, DefaultScreen(xx->dpy));
   xx->blackColor = BlackPixel(xx->dpy, DefaultScreen(xx->dpy));

   xx->w = XCreateSimpleWindow(xx->dpy,
      DefaultRootWindow(xx->dpy),
      0, 0, 
      xx->dpywdth, xx->dpyhght,
      0, xx->whiteColor,
      xx->whiteColor);

   XSelectInput(xx->dpy, xx->w, StructureNotifyMask);

   XMapWindow(xx->dpy, xx->w);

   xx->gc = XCreateGC(xx->dpy, xx->w, 0, NULL);

   xx->fontid = (Font) XLoadFont(xx->dpy,"12x24");

   XSetFont(xx->dpy,xx->gc,xx->fontid);

   XSetForeground(xx->dpy, xx->gc, xx->blackColor);

   xx->dfltscr = XDefaultScreenOfDisplay(xx->dpy);
   if (xx->dfltscr == NULL)
      {
      fprintf(stderr,"XDefaultScreenOfDisplay failed\n");
      perror("XDefaultScreenOfDisplay failed");
      exit(1);
      } /* if error */

   xx->cmap = XDefaultColormapOfScreen(xx->dfltscr);

   rslt = XAllocNamedColor(xx->dpy,xx->cmap,"red",
      &xx->scrdef,&xx->exctdef);

   if (rslt < 0)
      {
      fprintf(stderr,"XAllocNamedColor failed\n");
      perror("XAllocNamedColor failed");
      exit(1);
      } /* if error */
   xx->red = xx->scrdef.pixel;

   XSetWindowBorderWidth(xx->dpy, xx->w, 40);

   sprintf(title,"Random Bitmap");
   XStoreName(xx->dpy,xx->w,title);
   XSetIconName(xx->dpy,xx->w,title);

   while(1)
      {
      XEvent e;
      XNextEvent(xx->dpy, &e);
      if (e.type == MapNotify) break;
      } /* wait for window initialization */

   } /* initx */

/* initialize the state array for the subrand generator */
int subrand(xxfmt *xx);

void subrand_seed(xxfmt *xx, int p1)
	{
	int i;
	int j;
	int p2;
	int *p,*q;
	p = (int *) xx->state;
	q = (int *) xx->state + 55;
	while (p < q) *p++ = 0;
	xx->si = xx->sj = 0;
	p2 = 1;
 
	xx->state[0] = p1 % MOD;
	for (i = 1, j = 21; i < 55; i++, j += 21) {
		if (j >= 55) j -= 55;
		xx->state[j] = p2;
		if ((p2 = p1 - p2) < 0) p2 += MOD;
		p1 = xx->state[j];
	}
	xx->si = 0;
	xx->sj = 24;
	for (i = 0; i < 165; i++) subrand(xx);
	} /* subrand_seed */

/* generate a random number from 0 to 10^9 */
 
int subrand(xxfmt *xx)
	{
	int x;
	if (xx->si == xx->sj) subrand_seed(xx, 0);
 
	if (!xx->si--) xx->si = 54;
	if (!xx->sj--) xx->sj = 54;
	if ((x = xx->state[xx->si] - xx->state[xx->sj]) < 0) x += MOD;
	if (x == xx->first_seed)
	   {
	   fprintf(stderr,"subrand: wrap around "
	      "on count %.0f\n", xx->count);
	   exit(1);
	   } /* if wrap around */
 
	return xx->state[xx->si] = x;
	} /* subrand */
 
/* Initialize the subrand random number generator */
/* see http://rosettacode.org/wiki/Subtractive_generator */
/* for more information about subrand */

void start_rng(xxfmt *xx)
   {
   unsigned int sd;                /* seed */
   xx->ee = (eefmt *) eeglinit();
   sd = (eegl(xx->ee) | 1) & 0x7fffffff;
   xx->first_seed = sd;    /* for wrap around test */
   subrand_seed(xx, sd);
   } /* start_rng */

/* Generate one uniform sample from zero to one */

double gen_subrand(xxfmt *xx)
   {
   unsigned int x;
   double num;
   x = subrand(xx);
   num = (double) x / xx->subrand_mod;
   xx->count += 1.0;
   return(num);
   } /* gen_subrand */

int main()
   {
   xxfmt *xx;           /* structure for X Windows data */
   eefmt *ee;
   /* allocate memory for the X Windows structure */
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of mem */
   /* Start X Windows and open up a canvas (screen) */
   initx(xx);
   xx->subrand_mod = (double) MOD;
   /* initialize the eegl random number generator */
   ee = (eefmt *) eeglinit();
   /* set the run flag to run continuously */
   xx->runflg = 1;
   while(xx->runflg)   /* processing loop */
      {
      double num;
      int x;           /* column coordinate */
      int y;           /* row    coordinate */
      /* the coordinates use a 9 bit unsigned integer */
      /* this illustrates how to use eeglpwr() */
      num = gen_subrand(xx);
      x = (int) floor(num * 512.0);   /* set random column 0 to 511 */
      num = gen_subrand(xx);
      y = (int) floor(num * 512.0);   /* set random row    0 to 511 */
      num = gen_subrand(xx);
      /* if one, erase the pixel at x,y */
      if (num >= 0.5) XSetForeground(xx->dpy, xx->gc, xx->whiteColor);
      /* else, paint the pixel at x,y black */
      else XSetForeground(xx->dpy, xx->gc, xx->blackColor);
      /* draw (or erase) the pixel at x,y */
      XDrawPoint(xx->dpy,xx->w,xx->gc,x,y);
      /* test for keyboard interrupt */
      ifkey(xx);
      } /* while runflg != 0 */
   /* at end of job, delete the current window */
   XDestroyWindow(xx->dpy,xx->w);
   /* at end of job, close X Windows display */
   XCloseDisplay(xx->dpy);
   free(ee->state);        /* free eegl state array */
   free(ee);               /* free eegl structure */
   free(xx);               /* free X Windows structure */
   return(0);              /* normal end of job */
   } /* main */
