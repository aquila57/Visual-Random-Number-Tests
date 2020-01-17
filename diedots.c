/*
diedots.c Version 0.1.0. Random dots generator, RANDU 2D
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

/* to define the escape key */
#define XK_MISCELLANY 1
#define XK_LATIN1 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/times.h>
#include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <assert.h>
#include "visual.h"

/* structure for X Windows meta-data */
typedef struct wwstruct {
   int whiteColor,blackColor;
   int rootwh;      /* root window height */
   int rootww;      /* root window width  */
   int dpyhght;     /* display window height */
   int dpywdth;     /* display window width  */
   int repeat;
   int runflg;
   unsigned long red;
   Display *dpy;
   Window w;
   GC gc;
   Font fontid;
   Screen *dfltscr;
   Colormap cmap;
   XColor scrdef,exctdef;
   } wwfmt;

#define WDTH (512)
#define HGHT (512)

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s Dieharder_RNG_number\n", pgm);
   fprintf(stderr,"Example: %s 053\n", pgm);
   fprintf(stderr,"Where 053 is the taus2 generator\n");
   fprintf(stderr,"To see a list of "
      "dieharder generators:\n");
   fprintf(stderr,"dieharder -g -l\n");
   exit(1);
   } /* putstx */

/* X Windows code is based on: */
/* http://tronche.com/gui/x/xlib-tutorial/2nd-program-anatomy.html */
/* or */
/* http://tronche.com/gui/x  */

/* wait until key pressed */
void getkey(wwfmt *ww)
   {
   /* after each pause wait for command or exposure */

   XSelectInput(ww->dpy, ww->w,
      KeyPressMask|ExposureMask);

   while(1)
      {
      int symbol;
      XEvent e;
      XKeyEvent *k;
      XNextEvent(ww->dpy, &e);
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         ww->repeat = 0;
         if (symbol == XK_Escape || symbol == 'q')
            {
            ww->repeat = 0;
	    ww->runflg = 0;
            break;
            } /* if quit */
         else if (symbol == 'r' || symbol == 'n')
            {
            ww->repeat = 1;
            break;
            } /* if next */
         } /* if keypress event */
      else if (e.type == Expose)
         {
	 XClearWindow(ww->dpy,ww->w);
         continue;
         } /* if expose event */
      } /* wait for window shutdown */
   } /* getkey */

/* test keyboard for input character */
void ifkey(wwfmt *ww)
   {
   int msk;
   int symbol;
   int XCheckMaskEvent();
   XEvent e;
   XKeyEvent *k;

   msk = KeyPressMask|ExposureMask;

   XSelectInput(ww->dpy, ww->w, msk);

   while (XCheckMaskEvent(ww->dpy, msk, &e))
      {
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         if (symbol == XK_Escape
	    || symbol == XK_q)
            {
            ww->runflg = 0;
            } /* if quit */
         } /* if keypress event */
      else if (e.type == Expose)
         {
	 XClearWindow(ww->dpy,ww->w);
         } /* if expose event */
      } /* if event received */
   } /* ifkey */

/* initialize X Windows */
void initx(wwfmt *ww)
   {
   int rslt;
   char title[64];

   ww->dpy = XOpenDisplay(NULL);

   if (ww->dpy == NULL)
      {
      fprintf(stderr,"X Windows failure\n");
      exit(1);
      } /* if X Windows is not active */

   assert(ww->dpy);

   /* get dimensions of root window */
   ww->rootww = XDisplayWidth(ww->dpy,0);
   ww->rootwh = XDisplayHeight(ww->dpy,0);

   /* make display window smaller than root window */
   /* allow for menu bar on top */
   // ww->dpywdth = ww->rootww -  80;
   // ww->dpyhght = ww->rootwh - 100;
   ww->dpywdth = 512;        /* need a power of 2 */
   ww->dpyhght = 512;        /* need a power of 2 */

   ww->whiteColor = WhitePixel(ww->dpy, DefaultScreen(ww->dpy));
   ww->blackColor = BlackPixel(ww->dpy, DefaultScreen(ww->dpy));

   ww->w = XCreateSimpleWindow(ww->dpy,
      DefaultRootWindow(ww->dpy),
      0, 0, 
      ww->dpywdth, ww->dpyhght,
      0, ww->whiteColor,
      ww->whiteColor);

   XSelectInput(ww->dpy, ww->w, StructureNotifyMask);

   XMapWindow(ww->dpy, ww->w);

   ww->gc = XCreateGC(ww->dpy, ww->w, 0, NULL);

   ww->fontid = (Font) XLoadFont(ww->dpy,"12x24");

   XSetFont(ww->dpy,ww->gc,ww->fontid);

   XSetForeground(ww->dpy, ww->gc, ww->blackColor);

   ww->dfltscr = XDefaultScreenOfDisplay(ww->dpy);
   if (ww->dfltscr == NULL)
      {
      fprintf(stderr,"XDefaultScreenOfDisplay failed\n");
      perror("XDefaultScreenOfDisplay failed");
      exit(1);
      } /* if error */

   ww->cmap = XDefaultColormapOfScreen(ww->dfltscr);

   rslt = XAllocNamedColor(ww->dpy,ww->cmap,"red",
      &ww->scrdef,&ww->exctdef);

   if (rslt < 0)
      {
      fprintf(stderr,"XAllocNamedColor failed\n");
      perror("XAllocNamedColor failed");
      exit(1);
      } /* if error */
   ww->red = ww->scrdef.pixel;

   XSetWindowBorderWidth(ww->dpy, ww->w, 40);

   sprintf(title,"Random Bitmap");
   XStoreName(ww->dpy,ww->w,title);
   XSetIconName(ww->dpy,ww->w,title);

   while(1)
      {
      XEvent e;
      XNextEvent(ww->dpy, &e);
      if (e.type == MapNotify) break;
      } /* wait for window initialization */

   } /* initx */

void diepfx(xxfmt *xx)
   {
   int len;
   int rslt;
   int namesw;
   char buf[256];
   namesw = 0;
   xx->dieharder_rngname[0] = '\0';
   while (1)
      {
      len = scanf("%s", buf);
      if (len < 1)
         {
         if (feof(stdin))
	    {
	    fprintf(stderr,"diepfx: scanf end of file\n");
	    exit(1);
	    } /* if end of file */
         if (ferror(stdin))
            {
            perror("diepfx: read error\n");
            exit(1);
            } /* read error */
         fprintf(stderr,"diepfx: blank line, len %d\n", len);
         exit(1);
         } /* if eof or read error */
      if (len > 1)
         {
         fprintf(stderr,"diepfx: read error\n");
         fprintf(stderr,"scanf read more than "
            "one token %d\n", len);
         exit(1);
         } /* invalid input */
      rslt = strcmp(buf,"numbit:");
      if (!rslt) break;
      if (namesw)   /* buf = generator name? */
         {
	 strcpy(xx->dieharder_rngname,buf);
	 fprintf(stderr,"Dieharder RNG Name %s\n",
	    xx->dieharder_rngname);
	 namesw = 0;    /* turn off name switch */
	 } /* if generator name switch turned on */
      rslt = strcmp(buf,"generator");
      if (!rslt)
         {
	 namesw = 1;    /* turn on name switch */
	 } /* if generator statement */
      } /* read loop until numbit: */
   len = scanf("%s", buf);
   if (len < 1)
      {
      if (feof(stdin))
	 {
	 fprintf(stderr,"diepfx: scanf end of file\n");
	 exit(1);
	 } /* if end of file */
      if (ferror(stdin))
         {
         perror("getdie: read error\n");
         exit(1);
         } /* read error */
      fprintf(stderr,"getdie: blank line\n");
      exit(1);
      } /* if eof or read error */
   if (len > 1)
      {
      fprintf(stderr,"getdie: read error\n");
      fprintf(stderr,"scanf read more than "
         "one token %d\n", len);
      exit(1);
      } /* invalid input */
   rslt = strcmp(buf,"32");
   if (rslt)
      {
      fprintf(stderr,"diepfx: numbit not = 32\n");
      fprintf(stderr,"buf = %s\n", buf);
      exit(1);
      } /* numbit: not equal to 32 */
   } /* diepfx */

/* generate a random coordinate from zero to WDTH */
int gen_addr(xxfmt *xx)
   {
   int x;
   double num;
   xx->eofsw = 0;
   num = getdie(xx);   /* get number 0-1 */
   if (xx->eofsw)
      {
      fprintf(stderr,"gen_addr: end of "
         "file %.0f\n", xx->count);
      num = EOFDIE;
      } /* end of file condition */
   x = (int) floor(num * xx->dblsize);
   return(x);
   } /* gen_dbl */

int main(int argc, char **argv)
   {
   xxfmt *xx;
   wwfmt *ww;

   /*************************************************************/
   /* Allocate memory for the global structure.                 */
   /* This is a re-entrant program.                             */
   /*************************************************************/

   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx structure\n");
      exit(1);
      } /* out of memory */

   /*************************************************************/
   /* Allocate memory for the X Windows structure.              */
   /* This is a re-entrant program.                             */
   /*************************************************************/

   ww = (wwfmt *) malloc(sizeof(wwfmt));
   if (ww == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating ww structure\n");
      exit(1);
      } /* out of memory */

   /*************************************************************/
   /* initialize global data                                    */
   /*************************************************************/
   xx->dieharder_rngname[0] = '\0';
   xx->rngname = (char *) NULL;
   xx->generator = -1;
   xx->eofsw     = 0;
   /*************************************************************/
   /* obtain dieharder generator number parameter               */
   /*************************************************************/

   if (argc != 2) putstx(*argv);
   xx->generator = atoi(*(argv+1));
   if (xx->generator < 0 || xx->generator > 405)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */

   /*************************************************************/
   /* initialize numeric fields                                 */
   /*************************************************************/
   bld_maxint(xx);  /* build maxint table for dieharder RNGs */
   bld_rngtbl(xx);  /* build name table for dieharder RNGs */
   if (xx->maxint_tbl[xx->generator] == 0.0)
      {
      fprintf(stderr,"main: invalid random "
         "number generator %s\n", *(argv+1));
      putstx(*argv);
      } /* invalid generator */
   xx->modulus = xx->maxint_tbl[xx->generator];
   /****************************************************/
   diepfx(xx);    /* bypass dieharder prefix */
   xx->count = 0.0;
   xx->dblsize = (double) WDTH;
   /**************************************************************/
   /* Start X Windows and open up a canvas (screen) */
   /**************************************************************/
   initx(ww);
   /* set the run flag to run continuously */
   ww->runflg = 1;
   while(ww->runflg)   /* processing loop */
      {
      int x;           /* column coordinate */
      int y;           /* row    coordinate */
      double num;      /* >= 0.5 => white, < 0.5 => black */
      /* the coordinates use a 9 bit unsigned integer */
      /* this illustrates how to use eeglpwr() */
      x = gen_addr(xx);     /* set random column 0 to 511 */
      if (xx->eofsw) break;
      y = gen_addr(xx);     /* set random row    0 to 511 */
      if (xx->eofsw) break;
      /* if one, erase the pixel at x,y */
      num = getdie(xx);
      if (xx->eofsw) break;
      if (num >= 0.5) XSetForeground(ww->dpy, ww->gc, ww->whiteColor);
      /* else, paint the pixel at x,y black */
      else XSetForeground(ww->dpy, ww->gc, ww->blackColor);
      /* draw (or erase) the pixel at x,y */
      XDrawPoint(ww->dpy,ww->w,ww->gc,x,y);
      /* test for keyboard interrupt */
      ifkey(ww);
      } /* while runflg != 0 */
   /* at end of job, delete the current window */
   ww->runflg = 1;
   while (ww->runflg)
      {
      getkey(ww);
      } /* pause until quit */
   XDestroyWindow(ww->dpy,ww->w);
   /* at end of job, close X Windows display */
   XCloseDisplay(ww->dpy);
   free(xx);               /* free global structure */
   free(ww);               /* free X Windows structure */
   return(0);              /* normal end of job */
   } /* main */
