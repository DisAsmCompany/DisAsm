@setlocal
set PATH=%PATH%;%MINGW64%\bin
rmdir /s/q windows64-mingw
mkdir windows64-mingw
cd windows64-mingw
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS="-Wall -std=c99" ..
mingw32-make
DisAsmTest.exe
DisAsmBenchmark.exe %IPP_HOME%\ipp.bin
cd ..
