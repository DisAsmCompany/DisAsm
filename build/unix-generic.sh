#!/bin/sh
WORKDIR=$1
COMPILER=$2
rm -rf $1
mkdir $1
cp CMakeLists.txt $1/CMakeLists.txt
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER $WORKDIR/CMakeLists.txt
(cd $1 && make)
