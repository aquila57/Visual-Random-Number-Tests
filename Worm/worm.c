/*
worm.c - Pixel worm  Version 0.1.0
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

#include "worm.h"

void squirm(xxfmt *xx)
   {
   int exx;
   int wyy;
   int direction;
   struct timespec req;
   struct timespec rem;
   req.tv_sec  = 0;
   req.tv_nsec = 1e7;
   rem.tv_sec  = 0;
   rem.tv_nsec = 0;
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->blue);
   exx = xx->dpywdth >> 1;
   wyy = xx->dpyhght >> 1;
   XFillArc(xx->dpy,xx->w,xx->gc, exx, wyy,
      10, 10, 0, CIRCLE);
   direction = NORTH;
   isrtq(xx, exx, wyy, direction);
   while (xx->runflg)
      {
      int rslt;
      if (xx->qsize >= 1000)
	 {
	 int oldx;
	 int oldy;
	 oldx = xx->tail->next->exx;
	 oldy = xx->tail->next->wyy;
         XSetForeground(xx->dpy, xx->gc, xx->whiteColor);
         XFillArc(xx->dpy,xx->w,xx->gc, oldx, oldy,
            10, 10, 0, CIRCLE);
         XSetForeground(xx->dpy, xx->gc, xx->blue);
	 XFlush(xx->dpy);
         rmq(xx);
	 } /* if queue full */
      rslt = etauspwr(xx->et,4);
      if (xx->head->prev->direction == NORTH)
         {
	 if (!rslt)
	    {
	    exx--;
	    wyy--;
	    direction = NW;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    exx++;
	    wyy--;
	    direction = NE;
	    } /* if right */
	 else
	    {
	    wyy--;
	    direction = NORTH;
	    } /* else straight ahead */
	 } /* if previous N */
      else if (xx->head->prev->direction == NE)
         {
	 if (!rslt)
	    {
	    wyy--;
	    direction = NORTH;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    exx++;
	    direction = EAST;
	    } /* if right */
	 else
	    {
	    exx++;
	    wyy--;
	    direction = NE;
	    } /* else straight ahead */
	 } /* if previous NE */
      else if (xx->head->prev->direction == EAST)
         {
	 if (!rslt)
	    {
	    exx++;
	    wyy--;
	    direction = NE;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    exx++;
	    wyy++;
	    direction = SE;
	    } /* if right */
	 else
	    {
	    exx++;
	    direction = EAST;
	    } /* else straight ahead */
	 } /* if previous EAST */
      else if (xx->head->prev->direction == SE)
         {
	 if (!rslt)
	    {
	    exx++;
	    direction = EAST;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    wyy++;
	    direction = SOUTH;
	    } /* if right */
	 else
	    {
	    exx++;
	    wyy++;
	    direction = SE;
	    } /* else straight ahead */
	 } /* if previous SE */
      else if (xx->head->prev->direction == SOUTH)
         {
	 if (!rslt)
	    {
	    exx++;
	    wyy++;
	    direction = SE;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    exx--;
	    wyy++;
	    direction = SW;
	    } /* if right */
	 else
	    {
	    wyy++;
	    direction = SOUTH;
	    } /* else straight ahead */
	 } /* if previous SOUTH */
      else if (xx->head->prev->direction == SW)
         {
	 if (!rslt)
	    {
	    wyy++;
	    direction = SOUTH;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    exx--;
	    direction = WEST;
	    } /* if right */
	 else
	    {
	    exx--;
	    wyy++;
	    direction = SW;
	    } /* else straight ahead */
	 } /* if previous SW */
      else if (xx->head->prev->direction == WEST)
         {
	 if (!rslt)
	    {
	    exx--;
	    wyy++;
	    direction = SW;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    exx--;
	    wyy--;
	    direction = NW;
	    } /* if right */
	 else
	    {
	    exx--;
	    direction = WEST;
	    } /* else straight ahead */
	 } /* if previous WEST */
      else if (xx->head->prev->direction == NW)
         {
	 if (!rslt)
	    {
	    exx--;
	    direction = WEST;
	    } /* if left */
	 else if (rslt == 1)
	    {
	    wyy--;
	    direction = NORTH;
	    } /* if right */
	 else
	    {
	    exx--;
	    wyy--;
	    direction = NW;
	    } /* else straight ahead */
	 } /* if previous NW */
      if (exx >= xx->dpywdth) exx = 0;
      if (wyy >= xx->dpyhght) wyy = 0;
      if (exx < 0) exx = xx->dpywdth-1;
      if (wyy < 0) wyy = xx->dpyhght-1;
      XSetForeground(xx->dpy, xx->gc, xx->blue);
      XFillArc(xx->dpy,xx->w,xx->gc, exx, wyy,
         10, 10, 0, CIRCLE);
      XFlush(xx->dpy);
      isrtq(xx, exx, wyy, direction);
      ifkey(xx);
      nanosleep(&req,&rem);
      } /* for each squirm */
   } /* squirm */

int main(void)
   {
   xxfmt *xx;
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   xx->et = (etfmt *) etausinit();
   initx(xx);
   xx->head = (qfmt *) qinit();
   xx->tail = (qfmt *) qinit();
   xx->head->prev = xx->tail;
   xx->tail->next = xx->head;
   xx->qsize = 0;
   xx->runflg = 1;
   squirm(xx);
   while (xx->tail->next != xx->head) rmq(xx);
   free(xx->head);
   free(xx->tail);
   XDestroyWindow(xx->dpy,xx->w);
   XCloseDisplay(xx->dpy);
   free(xx->et->state);
   free(xx->et);
   return(0);
   } /* main */
