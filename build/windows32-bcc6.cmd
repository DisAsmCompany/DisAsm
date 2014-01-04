@setlocal
set PATH=%PATH%;%BORLANDC6%\bin
rmdir /s/q windows32-bcc6
mkdir windows32-bcc6
cd windows32-bcc6
cmake -G "Borland Makefiles" ..
make
DisAsmTest.exe
cd ..
