@setlocal
set PATH=%PATH%;%BORLANDC5%\bin
rmdir /s/q windows32-bcc5
mkdir windows32-bcc5
cd windows32-bcc5
cmake -G "Borland Makefiles" ..
make
DisAsmTest.exe
cd ..
