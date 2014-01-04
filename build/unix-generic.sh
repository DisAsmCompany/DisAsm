#!/bin/sh
WORKDIR=$1
COMPILER=$2
FLAGS=$3
rm -rf $WORKDIR
mkdir $WORKDIR
cd $WORKDIR
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" CMakeLists.txt
make VERBOSE=1
./DisAsmTest
cd ..
