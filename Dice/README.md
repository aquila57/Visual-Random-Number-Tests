# Roll dice

Roll a pair of dice.

Syntax:

./dice [-o] [-f filename]

Where -o is an optional parameter to display the odds of
rolling a pair of dice.

-f filename is an optional log filename.  The log file shows
date and time of each roll of the dice.

The background color behind the dice changes with each roll.
If the same numbers are rolled back to back, the background
color helps to distinguish between each roll of the dice.

Press the left mouse button or any key but 'q', to re-roll
the dice.

Press 'q' or the right mouse button to quit.

To install the dice program, first

Install X Windows

sudo apt-get install libx11-dev

chmod 700 *.sh

./inst.sh

To de-install the dice program,

./deinst.sh
