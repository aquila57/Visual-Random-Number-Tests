/*
worm.h - Pixel worm header file  Version 0.1.0
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

/* #degrees * 64 */
/* 360 * 64 = 23040 */
#define CIRCLE (23040)

#define EAST 0
#define NE 1
#define NORTH 2
#define NW 3
#define WEST 4
#define SW 5
#define SOUTH 6
#define SE 7

/* to define the escape key */
#define XK_MISCELLANY 1
#define XK_LATIN1 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <assert.h>
#include "etaus.h"

#define NIL (0)
#define DFLTRACER 999999999

typedef struct qstruct {
   struct qstruct *next;
   struct qstruct *prev;
   int exx;
   int wyy;
   int direction;
   } qfmt;

typedef struct xxstruct {
   int whiteColor,blackColor;
   int rootwh;      /* root window height */
   int rootww;      /* root window width  */
   int dpyhght;     /* display window height */
   int dpywdth;     /* display window width  */
   int repeat;
   int runflg;
   int red;
   int blue;
   Display *dpy;
   Window w;
   GC gc;
   Font fontid;
   Screen *dfltscr;
   Colormap cmap;
   XColor scrdef,exctdef;
   etfmt *et;
   qfmt *head;
   qfmt *tail;
   int qsize;
   } xxfmt;

void getkey(xxfmt *xx);
void ifkey(xxfmt *xx);
void initx(xxfmt *xx);
qfmt *qinit(void);
void isrtq(xxfmt *xx, int exx, int wyy, int direction);
void rmq(xxfmt *xx);
