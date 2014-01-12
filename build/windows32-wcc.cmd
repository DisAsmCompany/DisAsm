@setlocal
set INCLUDE=%WATCOM%\h;%WATCOM%\h\nt;
rmdir /s/q windows32-wcc
mkdir windows32-wcc
cd windows32-wcc
cmake -G "Watcom WMake" ..
wmake
DisAsmTest.exe
DisAsmBenchmark.exe %IPP_HOME%\ipp.bin
cd ..
