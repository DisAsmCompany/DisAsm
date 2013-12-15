#!/bin/sh
WORKDIR=$1
COMPILER=$2
FLAGS="-Wall -std=c99"
rm -rf $WORKDIR
mkdir $WORKDIR
cp CMakeLists.txt $WORKDIR/CMakeLists.txt
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" $WORKDIR/CMakeLists.txt
(cd $WORKDIR && make)
(cd $WORKDIR && ./DisAsmTest)
