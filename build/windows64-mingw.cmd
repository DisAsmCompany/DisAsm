@setlocal
set PATH=%PATH%;%MINGW64%\bin
rmdir /s/q windows64-mingw
mkdir windows64-mingw
copy CMakeLists.txt windows64-mingw\CMakeLists.txt
cd windows64-mingw
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS="-Wall -std=c99"
mingw32-make
DisAsmTest.exe
cd ..
