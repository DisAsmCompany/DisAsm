#!/bin/sh
WORKDIR=windows32-cygwin
COMPILER=gcc
FLAGS="-Wall -std=c99"
rm -rf $WORKDIR
mkdir $WORKDIR
cp CMakeLists.txt $WORKDIR/CMakeLists.txt
/usr/bin/cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" $WORKDIR/CMakeLists.txt
(cd $WORKDIR && /usr/bin/make VERBOSE=1)
(cd $WORKDIR && ./DisAsmTest)
