/*
srandgen.c Version 0.1.0. Random dots generator, subrand
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
/* subrand random number generator */
/* The cube of random dots is then fed into antiprism */
/* to create a 3D model that can be viewed and rotated */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "visual.h"

#define SMPLS (1000000)

#define SIZE (32)

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
   int i,j,k;
   unsigned int seed;      /* RANDU seed */
   xxfmt *xx;
   eefmt *ee;
   char cube[SIZE][SIZE][SIZE];
   xx = (xxfmt *) malloc(sizeof(xxfmt));
   if (xx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating xx\n");
      exit(1);
      } /* out of memory */
   /* initialize the eegl random number generator */
   xx->dblsize = (double) SIZE;
   xx->subrand_mod = (double) MOD;
   ee = (eefmt *) eeglinit();
   seed = eegl(ee) | 1;
   free(ee->state);        /* free eegl state array */
   free(ee);               /* free eegl structure */
   subrand_seed(xx, seed);   /* initialize subrand */
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
      double num;
      /* the coordinates use a 5 bit unsigned integer */
      /* set random column 0 to 31 */
      num = gen_subrand(xx);
      x = (int) floor(num * xx->dblsize);
      /* set random row 0 to 31 */
      num = gen_subrand(xx);
      y = (int) floor(num * xx->dblsize);
      /* set random depth 0 to 31 */
      num = gen_subrand(xx);
      z = (int) floor(num * xx->dblsize);
      /* if one, erase the pixel at x,y */
      num = gen_subrand(xx);
      if (num >= 0.5) bit = 1;   /* black dot */ 
      else bit = 0;              /* white dot */
      cube[x][y][z] = bit;
      } /* for each sample */
   /**************************************************************/
   /* write out the cube as a set of coordinates                 */
   /* for antiprism                                              */
   /**************************************************************/
   printf("0 0 0\n");
   for (i=0;i<SIZE;i++)
      {
      for (j=0;j<SIZE;j++)
         {
         for (k=0;k<SIZE;k++)
            {
	    if (cube[i][j][k] == 1)
	       {
	       printf("%d %d %d\n", i, j, k);
	       } /* if (cube[i][j][k] != '\0') */
            } /* for each z */
         } /* for each y */
      } /* for each x */
   printf("%d %d %d\n", SIZE, SIZE, SIZE);
   /**************************************************************/
   return(0);              /* normal end of job */
   } /* main */
