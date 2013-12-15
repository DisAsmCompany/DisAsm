#!/bin/sh
WORKDIR=unix-gprof
COMPILER=gcc
FLAGS="-pg"
rm -rf $WORKDIR
mkdir $WORKDIR
cp CMakeLists.txt $WORKDIR/CMakeLists.txt
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" -DCMAKE_EXE_LINKER_FLAGS="$FLAGS" $WORKDIR/CMakeLists.txt
(cd $WORKDIR && make VERBOSE=1)
for file in /home/sse4/ipp/ia32/*
do
	echo $file
	(cd $WORKDIR && ./DisAsmSample -p $file > /dev/null)
done
(cd $WORKDIR && gprof DisAsmSample DisAsmSample.gmon)
