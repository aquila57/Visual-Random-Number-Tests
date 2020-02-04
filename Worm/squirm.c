/*
squirm.c Version 0.1.0. Pixel squirm
Copyright (C) 2019 dondalah721@yahoo.com (Dondalah)

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
   req.tv_nsec = 1e6;
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
      if (xx->qsize >= 10000)
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
      while (1)
         {
         rslt = etauspwr(xx->et,2);
	 if (rslt != 3) break;
	 } /* accept 3 out of 4 */
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
	    wyy--;
	    direction = NORTH;
	    } /* if straight ahead */
	 else
	    {
	    exx++;
	    wyy--;
	    direction = NE;
	    } /* if right */
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
	    wyy--;
	    direction = NE;
	    } /* if straight ahead */
	 else
	    {
	    exx++;
	    direction = EAST;
	    } /* if right */
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
	    direction = EAST;
	    } /* if straight ahead */
	 else
	    {
	    exx++;
	    wyy++;
	    direction = SE;
	    } /* if right */
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
	    exx++;
	    wyy++;
	    direction = SE;
	    } /* if straight ahead */
	 else
	    {
	    wyy++;
	    direction = SOUTH;
	    } /* if right */
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
	    wyy++;
	    direction = SOUTH;
	    } /* if straight ahead */
	 else
	    {
	    exx--;
	    wyy++;
	    direction = SW;
	    } /* if right */
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
	    wyy++;
	    direction = SW;
	    } /* if straight ahead */
	 else
	    {
	    exx--;
	    direction = WEST;
	    } /* if right */
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
	    direction = WEST;
	    } /* if straight ahead */
	 else
	    {
	    exx--;
	    wyy--;
	    direction = NW;
	    } /* if right */
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
	    exx--;
	    wyy--;
	    direction = NW;
	    } /* if straight ahead */
	 else
	    {
	    wyy--;
	    direction = NORTH;
	    } /* if right */
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
