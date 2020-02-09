/*
pxlrace.c Version 1.1.0. Pixel Race
Copyright (C) 2001-2010 dondalah721@yahoo.com (Dondalah)

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

/* to define the escape key */
#define XK_MISCELLANY 1
#define XK_LATIN1 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/times.h>
#include <sys/types.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <assert.h>
#include <unistd.h>
#include "rnd.h"

/* Debian font */
/* #define FONT "8x16" */

/* Slackware font */
/* #define FONT "linux8x16" */

/* NONINTEL allows you to escape in the middle */
/* of the race.  This uses more resources. */
/* #define NONINTEL 1 */
/* #undef NONINTEL */
#undef NONINTEL

#define NIL (0)
#define DFLTRACER 999999999

int whiteColor,blackColor;
int rootwh;      /* root window height */
int rootww;      /* root window width  */
int dpyhght;     /* display window height */
int dpywdth;     /* display window width  */
int repeat;
int runflg;
int winticks;
int *toptent;
int *toptenw;
unsigned long red;
Display *dpy;
Window w;
GC gc;
Font fontid;
Screen *dfltscr;
Colormap cmap;
XColor scrdef,exctdef;

int first;
int racers;          /* number of racers in race */
int *racer;          /* list of racers from 2 to "racers" */

void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s [number of racers]\n",
      pgm);
   fprintf(stderr,"Where number of racers is 2 - %d\n",
      racers);
   fprintf(stderr,"Default is %d\n", racers);
   exit(1);
   } /* putstx */

void shwwinner()
   {
   int i,row,dest;
   char str[128];
   i = 0;
   row = 50;
   dest = dpywdth - 1;
   strcpy(str,"     Racer  Time");
   XDrawImageString(dpy,w,gc,10,row,str,strlen(str));
   row += 20;
   while (i < 10 && toptenw[i] < DFLTRACER)
      {
      sprintf(str,"%2d.  %4d   %4d",
         i+1, toptenw[i]+1, toptent[i]);
      XDrawImageString(dpy,w,gc,10,row,str,strlen(str));
      row += 20;
      i++;
      } /* list top ten */
   XDrawImageString(dpy,w,gc,10,380,"  r = rerun",11);
   XDrawImageString(dpy,w,gc,10,400,"esc = exit",10);
   XDrawImageString(dpy,w,gc,220,16,"Winner = ",9);
   XSetBackground(dpy, gc, whiteColor);
   XSetForeground(dpy, gc, red);
   XDrawPoint(dpy,w,gc,dest,first+25);
   XDrawPoint(dpy,w,gc,dest-1,first+25);
   XDrawPoint(dpy,w,gc,dest-2,first+25);
   XDrawPoint(dpy,w,gc,dest,first+24);
   XDrawPoint(dpy,w,gc,dest-1,first+24);
   XDrawPoint(dpy,w,gc,dest-2,first+24);
   XDrawPoint(dpy,w,gc,dest,first+26);
   XDrawPoint(dpy,w,gc,dest-1,first+26);
   XDrawPoint(dpy,w,gc,dest-2,first+26);
   XSetForeground(dpy, gc, blackColor);
   sprintf(str,"  Time = %4d", winticks);
   XDrawImageString(dpy,w,gc,220,36,str,strlen(str));
   } /* shwwinner */

void redraw()
   {
   int i,dist;
   char str[32];
   XSetBackground(dpy, gc, whiteColor);
   XSetForeground(dpy, gc, blackColor);
   XDrawImageString(dpy,w,gc,220,16,"Winner = ",9);
   sprintf(str, "%3d", first+1);
   XDrawImageString(dpy,w,gc,300,16,str,3);
   for (i=0;i<racers;i++)
      {
      dist = racer[i];
      if (i == first) XSetForeground(dpy, gc, red);
      XDrawPoint(dpy,w,gc,dist,i+25);
      if (dist > 0) XDrawPoint(dpy,w,gc,dist-1,i+25);
      if (i == first) XSetForeground(dpy, gc, blackColor);
      } /* for each lane */
   XDrawImageString(dpy,w,gc,10,380,"  r = rerun",11);
   XDrawImageString(dpy,w,gc,10,400,"esc = exit",10);
   if (toptenw[0] < DFLTRACER)
      shwwinner();
   } /* redraw */

/* X Windows code is based on: */
/* http://tronche.lri.fr:8000/gui/x/xlib-tutorial/2nd-program-anatomy.html */

void getkey()
   {
   /* after each race: wait for command or exposure */

   XSelectInput(dpy, w,
      KeyPressMask|ExposureMask);

   while(1)
      {
      int symbol;
      XEvent e;
      XKeyEvent *k;
      XNextEvent(dpy, &e);
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         repeat = 0;
         if (symbol == XK_Escape || symbol == 'q')
            {
            repeat = 0;
	    runflg = 0;
            break;
            } /* if quit */
         else if (symbol == 'r' || symbol == 'n')
            {
            repeat = 1;
            break;
            } /* if next */
         } /* if keypress event */
      else if (e.type == Expose)
         {
         redraw();
         continue;
         } /* if expose event */
      } /* wait for window shutdown */
   } /* getkey */

void ifkey()
   {
   int msk;
   int symbol;
   int XCheckMaskEvent();
   XEvent e;
   XKeyEvent *k;

   msk = KeyPressMask|ExposureMask;

   XSelectInput(dpy, w, msk);

   while (XCheckMaskEvent(dpy, msk, &e))
      {
      if (e.type == KeyPress)
         {
         k = (XKeyEvent *) &e;
         symbol = XLookupKeysym(k,0);
         if (symbol == XK_Escape
	    || symbol == XK_q)
            {
            runflg = 0;
            } /* if quit */
         } /* if keypress event */
      else if (e.type == Expose)
         {
         redraw();
         } /* if expose event */
      } /* if event received */
   } /* ifkey */

void initx()
   {
   int rslt;
   char title[64];

   dpy = XOpenDisplay(NIL);

   if (dpy == NULL)
      {
      fprintf(stderr,"X Windows failure\n");
      exit(1);
      } /* if X Windows is not active */

   assert(dpy);

   /* get dimensions of root window */
   rootww = XDisplayWidth(dpy,0);
   rootwh = XDisplayHeight(dpy,0);

   /* make display window smaller than root window */
   /* allow for menu bar on top */
   dpywdth = rootww -  80;
   dpyhght = rootwh - 100;

   whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
   blackColor = BlackPixel(dpy, DefaultScreen(dpy));

   w = XCreateSimpleWindow(dpy,
      DefaultRootWindow(dpy),
      0, 0, 
      dpywdth, dpyhght,
      0, whiteColor,
      whiteColor);

   XSelectInput(dpy, w, StructureNotifyMask);

   XMapWindow(dpy, w);

   gc = XCreateGC(dpy, w, 0, NIL);

   fontid = (Font) XLoadFont(dpy,FONT);

   XSetFont(dpy,gc,fontid);

   XSetForeground(dpy, gc, blackColor);

   dfltscr = XDefaultScreenOfDisplay(dpy);
   if (dfltscr == NULL)
      {
      fprintf(stderr,"XDefaultScreenOfDisplay failed\n");
      perror("XDefaultScreenOfDisplay failed");
      exit(1);
      } /* if error */

   cmap = XDefaultColormapOfScreen(dfltscr);

   rslt = XAllocNamedColor(dpy,cmap,"red",
      &scrdef,&exctdef);

   if (rslt < 0)
      {
      fprintf(stderr,"XAllocNamedColor failed\n");
      perror("XAllocNamedColor failed");
      exit(1);
      } /* if error */
   red = scrdef.pixel;

   XSetWindowBorderWidth(dpy, w, 40);

   sprintf(title,"pxlrace");
   XStoreName(dpy,w,title);
   XSetIconName(dpy,w,title);

#ifdef UPPERLEFT

   XMoveWindow(dpy,w,0,0);

#endif

   while(1)
      {
      XEvent e;
      XNextEvent(dpy, &e);
      if (e.type == MapNotify) break;
      } /* wait for window initialization */

   } /* initx */

int *initracers()
   {
   int *racer;
   racer = (int *) malloc(sizeof(int)*(racers+16));
   if (racer == NULL)
      {
      fprintf(stderr,"Out of memory allocating racer\n");
      exit(1);
      } /* out of mem */
   return(racer);
   } /* initracers */

int *inittoptent()
   {
   int i;
   int *toptent;
   toptent = (int *) malloc(sizeof(int)*16);
   if (toptent == NULL)
      {
      fprintf(stderr,"Out of memory " \
         "allocating toptent\n");
      exit(1);
      } /* out of mem */
   for (i=0;i<10;i++)
      {
      *(toptent+i) = DFLTRACER;
      } /* initialize toptent */
   return(toptent);
   } /* inittoptent */

int *inittoptenw()
   {
   int i;
   int *toptenw;
   toptenw = (int *) malloc(sizeof(int)*16);
   if (toptenw == NULL)
      {
      fprintf(stderr,"Out of memory " \
         "allocating toptenw\n");
      exit(1);
      } /* out of mem */
   for (i=0;i<10;i++)
      {
      *(toptenw+i) = DFLTRACER;
      } /* initialize toptenw */
   return(toptenw);
   } /* inittoptenw */

void initpxl()
   {
   int i;
   first = 0;
   XSetBackground(dpy, gc, whiteColor);
   XSetForeground(dpy, gc, blackColor);
   XDrawImageString(dpy,w,gc,220,16,"Leader = ",9);
   for (i=0;i<racers;i++)
      {
      racer[i] = 0;
      XDrawPoint(dpy,w,gc,0,i+25);
      } /* initialize participants */
   } /* initpxl */

void race()
   {
   int i,tmpt,tmpw,holdt,holdw;
   int isrtsw;
   clock_t strtclk,clk;
   int dest,lane,dist,prevdist;
   int frstdist;
   char str[64];
   struct tms t;
   XSetBackground(dpy, gc, whiteColor);
   dest = dpywdth - 1;
   strtclk = times(&t);
   frstdist = 0;
   while (frstdist < dest)
      {
      lane = rndnum(racers,sd);
      dist = ++racer[lane];
      if (dist > 1)
         {
         prevdist = dist - 2;
         XSetForeground(dpy, gc, whiteColor);
         XDrawPoint(dpy,w,gc,prevdist,lane+25);
         } /* if room to clear */
      XSetForeground(dpy, gc, blackColor);
      XDrawPoint(dpy,w,gc,dist,lane+25);
      if (dist > frstdist)
         {
         frstdist = dist;
         first = lane;
         /* because of exposure */
         XDrawImageString(dpy,w,gc,220,16,"Leader = ",9);
         sprintf(str, "%3d", first+1);
         XDrawImageString(dpy,w,gc,300,16,str,4);
         XDrawImageString(dpy,w,gc,340,16," of ",4);
         sprintf(str, "%3d", racers);
         XDrawImageString(dpy,w,gc,375,16,str,4);
         } /* if new leader */
#ifdef NONINTEL
      ifkey();
      if (!runflg) return;
#endif
      } /* for each step */
   clk = times(&t);
   winticks = clk - strtclk;
   i = 0;
   while (i < 10)
      {
      isrtsw = 0;
      if (winticks < toptent[i])
         isrtsw = 1;
      else if (winticks == toptent[i]
         && first < toptenw[i])
         isrtsw = 1;
      if (isrtsw)
         {
         tmpt = toptent[i];
         tmpw = toptenw[i];
         toptent[i] = winticks;
         toptenw[i++] = first;
         while (i < 10)
            {
            holdt = toptent[i];
            toptent[i] = tmpt;
            tmpt = holdt;
            holdw = toptenw[i];
            toptenw[i++] = tmpw;
            tmpw = holdw;
            } /* shift right */
         } /* insert here */
      else i++;
      } /* insert winner */
   shwwinner();
   } /* race */

int main(int argc, char **argv)
   {
   int i;
   int rslt;
   char str[256];
   sd = (unsigned char *) initrnd();
   initx();
   racers = dpyhght - 30;
   if (argc > 2)
      {
      fprintf(stderr,"%s: Too many arguments\n", *argv);
      putstx(*argv);
      } /* too many args */
   else if (argc == 2)
      {
      rslt = strcmp(*(argv+1), "-h");
      if (!rslt)
         {
         XSetBackground(dpy, gc, whiteColor);
         XSetForeground(dpy, gc, blackColor);
         sprintf(str, "Usage: %s "\
	    "[number of racers]", *argv);
         XDrawImageString(dpy,w,gc,200,100,str,strlen(str));
         sprintf(str, "Where number of racers "
	    "is 2 - %3d", racers);
         XDrawImageString(dpy,w,gc,200,140,str,strlen(str));
         sprintf(str, "Default is %3d", racers);
         XDrawImageString(dpy,w,gc,200,180,str,strlen(str));
         sprintf(str, "Press <escape> to quit");
         XDrawImageString(dpy,w,gc,200,220,str,strlen(str));
	 runflg = 1;
	 while (runflg)
	    {
	    runflg = 1;
	    getkey();
	    } /* getkey escape */
	 putstx(*argv);
	 } /* if help */
      i = atoi(*(argv+1));
      if (i < 2 || i > racers)
         {
         fprintf(stderr,"%s: Invalid number " \
	    "of racers\n", *argv);
         putstx(*argv);
	 } /* wrong # of racers */
      racers = i;
      } /* one argument */
   racer   = (int *) initracers();
   toptent = (int *) inittoptent();
   toptenw = (int *) inittoptenw();
   XDrawPoint(dpy,w,gc,100,0);
   repeat = runflg = 1;
   while (repeat && runflg)
      {
      repeat = 0;
      initpxl();
      race();
      if (runflg)
	 {
	 getkey();
         if (repeat)
            {
            XClearWindow(dpy,w);
            } /* if rerun */
         } /* if still running */
      } /* for each race */
   return(0);
   } /* main */
