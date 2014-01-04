rmdir /s/q windows32-msvc2010
mkdir windows32-msvc2010
cd windows32-msvc2010
cmake -G "Visual Studio 10" -DCMAKE_C_FLAGS="/W4" ..
"%VS100COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
