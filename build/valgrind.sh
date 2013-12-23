#!/bin/sh
WORKDIR=unix-valgrind
COMPILER=gcc
FLAGS="-Wall -Wextra -pedantic -std=c99"
VALGRIND="valgrind -v --track-origins=yes --track-fds=yes --leak-check=full"
rm -rf $WORKDIR
mkdir $WORKDIR
cp CMakeLists.txt $WORKDIR/CMakeLists.txt
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" $WORKDIR/CMakeLists.txt
(cd $WORKDIR && make VERBOSE=1)
for file in /home/sse4/ipp/ia32/*
do
	echo $file
	(cd $WORKDIR && $VALGRIND ./DisAsmSample -p -q $file > /dev/null)
done
