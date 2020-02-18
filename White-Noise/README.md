# White Noise Generator

The white noise generator in this directory uses a random
number generator, called etaus.  Etaus generates 44100 random
samples per second.  The white noise generator accepts a
single parameter for the duration of the white noise, in seconds.

./white #seconds

Example,

./white 10

This example produces a WAVE file of 10 seconds of white noise.

----------------

Random number generator used in this test.

etaus

The eetaus random number generator is explained in the repository
"etaus".  That is a random number generator based on the Tausworthe
algorithm by Pierre L'Ecuyer at the University of Montreal.
Etaus uses the Bays-Durham shuffle.  The period length of this
generator approximates 1.2 * 10^61036 generations.  That is a
long period length, that never terminates, or wraps around.  The
etaus generator passes this test.

-----------------------------------------------------------

The following subroutines are used in the white noise generator.

Etaus subroutines.

etausabt.c - print copyright and a summary of the GNU Public License.

etausbit.c - output a random bit

etaus.c - core randomizer, outputs a 32 bit unsigned integer.

etausdspl.c - display the internal state of the generator.

etausfrac.c - generate a 53 bit fraction between zero and one.

etausinit.c - initialize the generator based on date, time, and
number of ticks since the machine was booted.

etausint.c - generate a random integer between zero and a limit
minus one.

etauspwr.c - generate from 1 to 32 random bits.

etausstrt.c - initialize the generator based on three seed parameters.

etausunif.c - generate a 32 bit fraction between zero and one.

--------------------------------------------------------------

