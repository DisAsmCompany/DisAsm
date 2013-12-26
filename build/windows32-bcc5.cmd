@setlocal
set PATH=%PATH%;%BORLANDC5%\bin
rmdir /s/q windows32-bcc5
mkdir windows32-bcc5
copy CMakeLists.txt windows32-bcc5\CMakeLists.txt
cd windows32-bcc5
cmake -G "Borland Makefiles"
make
DisAsmTest.exe
cd ..
