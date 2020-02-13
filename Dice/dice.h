/*
dice.h - Random dice header file  Version 0.1.0
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

/* X Windows code is based on: */
/* http://tronche.lri.fr:8000/gui/x/xlib-tutorial/2nd-program-anatomy.html */

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
#include <sys/stat.h>
#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <assert.h>
#include <gsl/gsl_rng.h>
#include "etaus.h"

#define NIL (0)

#define SCRW 190
#define SCRH 170
#define LEFT   20
#define RIGHT 110
#define CIRCLE 23040

typedef struct xxstruct {
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
   double modulus;
   unsigned int seed;
   unsigned int lfsr0;
   unsigned int lfsr;
   unsigned int major;
   unsigned int minor;
   int out;
   int lowbit;
   unsigned int fibo1;
   unsigned int fibo2;
   unsigned int fibo3;
   int leftlean,rghtlean;
   int exposesw;
   int bgsw,altbg;
   unsigned long maroon,ivory,navy;
   int scrw,scrh;
   etfmt *et;
   gsl_rng *rng;
   gsl_rng_type *rngtype;
   } xxfmt;

void redraw(xxfmt *xx);
void getkey(xxfmt *xx);
void ifkey(xxfmt *xx);
void initx(int wdth, int hght, xxfmt *xx);
int  opn(char *fname);
void cls(int hndl);
void putstx(char *pgm);
void die1(int left, xxfmt *xx);
void die2(int left, xxfmt *xx);
void die3(int left, xxfmt *xx);
void die4(int left, xxfmt *xx);
void die5(int left, xxfmt *xx);
void die6(int left, xxfmt *xx);
void setclr(xxfmt *xx);
void shwodds(int left, int right, xxfmt *xx);
void wrtlog(int left, int right, int hndl, xxfmt *xx);
