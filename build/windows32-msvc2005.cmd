rmdir /s/q windows32-msvc2005
mkdir windows32-msvc2005
cd windows32-msvc2005
cmake -G "Visual Studio 8 2005" -DCMAKE_C_FLAGS="/W4" ..
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
