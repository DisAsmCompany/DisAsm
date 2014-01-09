#!/bin/sh
chmod +x unix-generic.sh
./unix-generic.sh unix-gcc gcc "-Wall -Wextra -pedantic -std=c99 -D_POSIX_C_SOURCE=1"
