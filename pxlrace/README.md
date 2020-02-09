# Pixel Race

Pixel race is a random race between 670 pixels to see which pixel
is the first to reach the right side of the screen.  At each
step of the race, a random racer is chosen to advance one pixel.
Follow the leader at the top of the screen to see how many times
the leadership changes during the race.

At the end of the race, the program shows the top ten winners.

Press 'r' to re-run the race.

Press 'q' or escape to quit the race, either during or after
a race.

The race has been slowed down by nanosleep(), so that it is easier
to watch.  Notice the optical illusion, where the column of pixels
appear to be rotating in a counter clockwise direction.

There are three versions of the race program in this directory,
depending on which random number generator is being used.

-------------------------------------------------------------------

eegl64 generator.

To run the race, type:

./eeglrace

-------------------------------------------------------------------

etaus generator.

To run the race, type:

./etausrace

-------------------------------------------------------------------

GNU Scientific Library generators.

To run the race, type:

./tstgsl.sh RNG_name

Where RNG_name is the name of the generator.

Example,

./tstgsl.sh taus2

This example runs the race with the taus2 generator.

To see a list of GSL generators, type

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

inst.sh

To de-install pxlrace:

deinst.sh
