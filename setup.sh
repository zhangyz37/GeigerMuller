#!/bin/bash
#
# Author: Balázs Demeter (balazsdemeter92@gmail.com)
# Version: 2.0
#
# Script for build and make Geant4 simulation of Geiger-Muller counter

mkdir gm_build
cd gm_build
cmake ../
make
echo Setup complete.
