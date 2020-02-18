/* white.c - White noise  Version 0.1.0                              */
/* Copyright (C) 2020 aquila57 at github.com                         */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "etaus.h"

#define VOL (16384.0)

/* structure for defining the WAVE file header */

typedef struct hdrstruct {
   /******************************************************/
   /* RIFF chunk                                         */
   /******************************************************/
   char riff[4];            /* 'RIFF'             */
   int totlen;              /* 88200 * #secs + 36 */
   char wave[4];            /* 'WAVE'             */
   /******************************************************/
   /* format chunk                                       */
   /******************************************************/
   char fmt[4];             /* 'fmt '             */
   int fmtsz;               /* 16 = PCM */
   short int fmttag;        /* 1 = wave file */
   short int channels;      /* 1 = mono, 2 = stereo */
   int smplpersec;          /* 44100 samples per second */
   int bytepersec;          /* 88200 bytes per second */
   short int blkalgn;       /* 16 / 2 = 8 bytes per sample*/
   short int bitsmpl;       /* 16 bits per sample*/
   /******************************************************/
   /* data chunk                                         */
   /******************************************************/
   char datapfx[4];         /* 'data' */
   int datasz;              /* data length = 88200 * #secs */
   /* data follows in 16 bit samples */
   /* in the case of white noise, each sample is a random */
   /* number from +16384 to -16384                        */
   } hdrfmt;

void putstx(char *pgm)
   {
   fprintf(stderr,"White Noise\n");
   fprintf(stderr,"Usage: %s #seconds\n", pgm);
   fprintf(stderr,"Example: %s 60\n", pgm);
   exit(1);
   } /* putstx */

int main(int argc, char **argv)
   {
   int i;           /* loop counter for total #samples */
   int secs;        /* seconds of duration */
   unsigned char *p,*q;       /* pointer to header */
   etfmt *et;       /* structure for etaus generator */
   hdrfmt *hh;      /* heap memory for the header */
   /******************************************************/
   /* read the parameter                                 */
   /******************************************************/
   if (argc != 2) putstx(*argv);
   secs = atoi(*(argv+1));
   if (secs < 1 || secs > 60)
      {
      fprintf(stderr,"Invalud #seconds %s\n", *(argv+1));
      fprintf(stderr,"#seconds is 1-60\n");
      putstx(*argv);
      } /* invalid #seconds */
   /******************************************************/
   /* allocate the WAVE file header                      */
   /******************************************************/
   hh = (hdrfmt *) malloc(sizeof(hdrfmt));    
   if (hh == NULL)
      {
      fprintf(stderr,"main: out of memory allocating "
         "allocating hh header structure\n");
      exit(1);
      } /* out of memory */
   /******************************************************/
   /* format the header                                  */
   /******************************************************/
   strncpy(hh->riff,"RIFF",4);
   hh->totlen = ((44100 * secs) << 1) + 36;   /* secs seconds */
   strncpy(hh->wave,"WAVE",4);
   /******************************************************/
   strncpy(hh->fmt,"fmt ",4);   /* format chunk */
   hh->fmtsz      = 16;         /* PCM = 16 */
   hh->fmttag     = 1;          /* 1 = wave file */
   hh->channels   = 1;          /* 1 = mono, 2 = stereo */
   hh->smplpersec = 44100;      /* 44100 samples per second */
   hh->bytepersec = 88200;      /* 88200 bytes per second */
   hh->blkalgn    = 2;          /* (16 / 8) * 1 = 2 bytes per sample */
   hh->bitsmpl    = 16;         /* 16 bits per sample */
   /******************************************************/
   strncpy(hh->datapfx,"data",4);     /* data chunk */
   /* 88200 x #seconds */
   hh->datasz = 88200 * secs;         /* data length in seconds */
   /***********************************************************/
   /* write header to stdout                                  */
   /***********************************************************/
   p = (unsigned char *) hh;          /* start of header */
   q = (unsigned char *) hh + 44;     /* end of header */
   while (p < q)
      {
      printf("%c", *p++);
      } /* for each byte in header */
   /***********************************************************/
   /* write data chunk as #seconds of white noise             */
   /***********************************************************/
   /* initialize random number generator etaus                */
   /***********************************************************/
   et = (etfmt *) etausinit();
   /* total number of samples */
   i = 44100 * secs;
   while (i--)
      {
      int ivol;          /* integer volume */
      int byte1;
      int byte2;
      ivol = (int) etaus(et) >> 16;          /* integer volume */
      byte1 = ivol & 255;           /* little endian low  byte */
      byte2 = (ivol >> 8) & 255;    /* little endian high byte */
      printf("%c%c", (unsigned char) byte1,
         (unsigned char) byte2);
      } /* for each sample */
   free(et->state);
   free(et);
   free(hh);
   return(0);
   } /* main */
