# Random Walk

Random walk is a visual test in two dimensions.  A horizontal line
is placed in the middle of the screen.  For each generation of the
random number generator, the left most point is shifted up or down
one pixel, and the rest of the horizontal line is shifted to the
right by one pixel.  An optical illusion is created, which appears
like a wavy line moving to the right.  A red horizontal line shows
where the middle of the screen is.

The only generator, which fails badly in the random walk, is the
sine wave generator.  Fibonacci, LFSR, and RANDU are weak generators,
but they do not fail the random walk.  The etaus generator is
expected to pass the random walk test, as are most of the GSL
collection of generators.

-------------------------------------------------------------------

etaus random number generator.

Program execution:

./ranwlk

-------------------------------------------------------------------

fibonacci random number generator.

Program execution:

./fibowlk

-------------------------------------------------------------------

LFSR random number generator.

Program execution:

./lfsrwlk

-------------------------------------------------------------------

RANDU random number generator.

Program execution:

./ruwalk

-------------------------------------------------------------------

sine wave random number generator.

Program execution:

./sinewlk

This generator fails the random walk test.  The line deviates to
the top of the screen.

-------------------------------------------------------------------

GNU Scientific Library of random number generators.

Program execution:

./tstgsl.sh RNG_name

Example,

./tstgsl.sh taus2

To see a list of GSL generators, enter

./tstgsl.sh ?

-------------------------------------------------------------------

Installation instructions:

Install X Windows:

sudo apt-get install libx11-dev

Install the GNU Scientific Library

sudo apt-get install libgsl2
sudo apt-get install libgsl-dev
sudo apt-get install gsl-ref-html

chmod 700 *.sh

./inst.sh

To de-install:

./deinst.sh
