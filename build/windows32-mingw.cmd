@setlocal
set PATH=%PATH%;%MINGW32%\bin
rmdir /s/q windows32-mingw
mkdir windows32-mingw
cd windows32-mingw
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS="-Wall -std=c99" ..
mingw32-make
DisAsmTest.exe
cd ..
