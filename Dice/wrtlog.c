/*
wrtlog.c - Write to log file  Version 0.1.0
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

#include "dice.h"

void wrtlog(int left, int right, int hndl, xxfmt *xx)
   {
   int tot;
   int len;
   int wrtlen;
   time_t t;
   struct tm *lcltm;
   char *dtstr;
   char *p;
   char logstr[128];
   time(&t);
   lcltm = (struct tm *) localtime(&t);
   dtstr = (char *) asctime(lcltm);
   p = (char *) dtstr + strlen(dtstr) - 1;
   *p = ' ';   /* remove eol char */
   tot = left + right;
   sprintf(logstr,"%s %d + %d = %2d\n",
      dtstr, left, right, tot);
   len = strlen(logstr);
   wrtlen = write(hndl,logstr,len);
   if (wrtlen == len) return;
   perror("dice: log error");
   exit(1);
   } /* wrtlog */
