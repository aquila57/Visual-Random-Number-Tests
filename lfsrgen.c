/*
lfsrgen.c Version 0.1.0. Random 3D dots, LFSR generator
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

/* This program creates a 3D cube of dots using the */
/* 64 bit LFSR random number generator */
/* The cube of random dots is then fed into antiprism */
/* to create a 3D graph that can be viewed and rotated */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "eegl.h"

#define MYLFSROUT (out = (((lfsr >> 4) \
   ^ (lfsr >> 3) \
   ^ (lfsr >> 1) \
   ^ (lfsr >> 0)) & 1))

#define MYLFSRLOWBIT (lowbit = major & 1)

#define MYLFSRROLL (lfsr0 = major = \
(lfsr0 >> 1) | (out << 31))

#define MYLFSRCARRY (lfsr = minor = \
(lfsr >> 1) | (lowbit << 31))

#define MYLFSR (MYLFSROUT,MYLFSRLOWBIT,MYLFSRROLL,MYLFSRCARRY)

#define SMPLS (1000000)

#define SIZE (32)

int main()
   {
   char cube[32][32][32];
   int i;
   unsigned int lfsr0;
   unsigned int lfsr;
   unsigned int major;
   unsigned int minor;
   unsigned int lowbit;
   unsigned int out;
   eefmt *ee;
   /* initialize the eegl random number generator */
   ee = (eefmt *) eeglinit();
   lfsr0 = major = eegl(ee);
   lfsr  = minor = eegl(ee);
   lowbit = out = 0;
   free(ee->state);        /* free eegl state array */
   free(ee);               /* free eegl structure */
   /**************************************************************/
   /* initialize the cube to zeros                               */
   /**************************************************************/
   for (i=0;i<SIZE;i++)
      {
      int j;
      for (j=0;j<SIZE;j++)
         {
         int k;
         for (k=0;k<SIZE;k++)
            {
	    cube[i][j][k] = '\0';
            } /* for each z */
         } /* for each y */
      } /* for each x */
   /**************************************************************/
   i = SMPLS;
   while(i--)   /* generating loop */
      {
      int bit;         /* color bit */
      int x;           /* column coordinate */
      int y;           /* row    coordinate */
      int z;           /* dept   coordinate */
      /* the coordinates use a 5 bit unsigned integer */
      MYLFSR;
      x = lfsr >> 27;    /* set random column 0 to 31 */
      MYLFSR;
      y = lfsr >> 27;    /* set random row    0 to 31 */
      MYLFSR;
      z = lfsr >> 27;    /* set random depth  0 to 31 */
      /* if one, set the dot at x,y,z to black */
      MYLFSR;
      bit = out;      /* choose black or white dot */
      cube[x][y][z] = bit;
      } /* for each sample */
   /**************************************************************/
   /* write out the cube as a set of coordinates                 */
   /* for antiprism                                              */
   /**************************************************************/
   printf("0 0 0\n");
   for (i=0;i<SIZE;i++)
      {
      int j;
      for (j=0;j<SIZE;j++)
         {
         int k;
         for (k=0;k<SIZE;k++)
            {
	    if (cube[i][j][k])
	       printf("%d %d %d\n", i, j, k);
            } /* for each z */
         } /* for each y */
      } /* for each x */
   printf("%d %d %d\n", SIZE, SIZE, SIZE);
   /**************************************************************/
   return(0);              /* normal end of job */
   } /* main */
