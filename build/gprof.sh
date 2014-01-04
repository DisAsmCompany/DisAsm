#!/bin/sh
WORKDIR=unix-gprof
COMPILER=gcc
FLAGS="-pg"
rm -rf $WORKDIR
mkdir $WORKDIR
cd $WORKDIR
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" -DCMAKE_EXE_LINKER_FLAGS="$FLAGS" ..
make VERBOSE=1
for file in /home/sse4/ipp/ia32/*
do
	echo $file
	./DisAsmSample -p -q $file > /dev/null
done
gprof DisAsmSample DisAsmSample.gmon
cd ..
