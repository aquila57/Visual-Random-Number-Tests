#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "eegl.h"

#define SMPLS (1000000)

#define SIZE (32)

#define MOD (1000000000)

#define EOFDIE (-999999999.0)

typedef struct xxstruct {
   char *rngname;
   char dieharder_rngname[128];
   char rngtbl[1000][64];
   int generator;
   int eofsw;
   unsigned int si;
   unsigned int sj;
   unsigned int first_seed;
   unsigned int state[55];
   double dblsize;
   double count;
   double modulus;
   double subrand_mod;
   double maxint_tbl[2048];
   eefmt *ee;
   } xxfmt;

double getdie(xxfmt *xx);

void diepfx(xxfmt *xx);

void bld_maxint(xxfmt *xx);

void bld_rngtbl(xxfmt *xx);

int gen_addr(xxfmt *xx);
