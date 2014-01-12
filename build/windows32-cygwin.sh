#!/bin/sh
WORKDIR=windows32-cygwin
COMPILER=gcc
FLAGS="-Wall -Wextra -pedantic -std=c99"
rm -rf $WORKDIR
mkdir $WORKDIR
cd $WORKDIR
/usr/bin/cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" -DCMAKE_LEGACY_CYGWIN_WIN32=0 ..
/usr/bin/make VERBOSE=1
./DisAsmTest
./DisAsmBenchmark %IPP_HOME%\ipp.bin
cd ..
