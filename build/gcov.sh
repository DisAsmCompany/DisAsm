#!/bin/sh
WORKDIR=unix-gcov
COMPILER=gcc
FLAGS="-fprofile-arcs -ftest-coverage -O0"
rm -rf $WORKDIR
mkdir $WORKDIR
cp CMakeLists.txt $WORKDIR/CMakeLists.txt
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=$COMPILER -DCMAKE_C_FLAGS="$FLAGS" $WORKDIR/CMakeLists.txt
(cd $WORKDIR && make)
$WORKDIR/DisAsmTest
(cd $WORKDIR && lcov -t 'DisAsm' -o gcov.info -c -d .)
(cd $WORKDIR && genhtml -o result gcov.info)
(cd $WORKDIR && cp -R result/ /home/sse4/site/gcov/)
