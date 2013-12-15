rmdir /s/q windows32-bcc
mkdir windows32-bcc
copy CMakeLists.txt windows32-bcc\CMakeLists.txt
cd windows32-bcc
cmake -G "Borland Makefiles"
make
DisAsmTest.exe
cd ..
