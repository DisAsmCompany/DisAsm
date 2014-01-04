#!/bin/sh
WORKDIR=unix-gcov
COMPILER=gcc
FLAGS="-fprofile-arcs -ftest-coverage -O0"
rm -rf $WORKDIR
mkdir $WORKDIR
cd $WORKDIR
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" ..
make VERBOSE=1
./DisAsmTest
lcov -t 'DisAsm' -o gcov.info -c -d .
genhtml -o result gcov.info
cp -R result/ /home/sse4/site/gcov/
cd ..
