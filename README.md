# Visual Random Number Test

The visual random number test shows whether random number
generators appear to be uniformly distributed on a 2D or 3D
graph.

Another type of test, the worm random walk, is in a subdirectory,
called Worm.  Read the README.md file in that directory and
follow the installation instructions given there.

The visual test uses a random number generator to calculate
random cartesian coordinates on a graph.  Each coordinate
is a separate generation of the generator.  First the
x coordinate is generated.  Then the y coordinate is
generated.  If the test is for a 3D graph, the z coordinate
is also generated.  Finally a random choice is made to
determine if a dot is present or absent at the chosen
location.

In the 2D test, the dots are generated continuously to
show whether the pattern on the screen appears to be uniformly
dynamic.  The RANDU and fibonacci generators produce diagonal
stripes.  The sine wave generator produces increased activity
around the right edge and bottom edge.  The LFSR generator
produces four diagonal lines.  The other generators appear uniform
and random on the screen.

In the 3D test, a 32x32x32 cube is populated with random dots.
Then the cube is formated and portrayed in 3d by the antiprism
package.  The RANDU generator produces parallel planes.
The fibonacci generator produces four parallel planes. 
The LFSR generator produces four diagonal lines.
The sine wave generator produces a smaller random cube with
empty space around three sides.  The uni generator from the
GNU Scientific Library produces a smaller random cube with
empty space around four sides.  The other generators appear
uniform and random in the cube.

The GNU Scientific Library of random number generators all
appear random and uniform with the exception of the randu.
The GSL randu generator appears with planes in 3D, like the
RANDU program in this repository.  The GSL uni generator appears
random in 2D and 3D, whereas the same generator from dieharder
appears small in 3D.

The dieharder collection of random number generators all
appear random and uniform with the exception of the XOR
and the uni generators.  The XOR generator aborts with a
segmentation fault in dieharder.  The uni generator populates
only a corner of the 32x32x32 cube.  

-----------------------------------------------------------

If you have a random number generator that you want to include
in this repository, you are welcome to submit your generator for
inclusion.

Read the INSTALL and TESTING documents for more information
about how to use this repository.
