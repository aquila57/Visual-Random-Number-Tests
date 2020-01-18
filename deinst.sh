#!/bin/bash
make -f eegllib.mak clean
make -f etauslib.mak clean
make -f libvis.mak clean
make -f eegldots.mak clean
make -f etausdots.mak clean
make -f fibodots.mak clean
make -f lfsrdots.mak clean
make -f sinedots.mak clean
make -f rudots.mak clean
make -f sranddots.mak clean
make -f gsldots.mak clean
make -f eeglgen.mak clean
make -f etausgen.mak clean
make -f rugen.mak clean
make -f fibogen.mak clean
make -f lfsrgen.mak clean
make -f sinegen.mak clean
make -f srandgen.mak clean
make -f gslgen.mak clean
make -f gendie.mak clean
make -f diedots.mak clean
rm -f coords.txt
rm -f cube_frame.off
