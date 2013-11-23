#!/bin/sh
WORKDIR=$1
COMPILER=$2
FLAGS="-Wall -std=c99"
rm -rf $1
mkdir $1
cp CMakeLists.txt $1/CMakeLists.txt
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" $WORKDIR/CMakeLists.txt
(cd $1 && make)
