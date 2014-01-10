rmdir /s/q windows32-msvc2012
mkdir windows32-msvc2012
cd windows32-msvc2012
cmake -G "Visual Studio 11" -T "v110_xp" -DCMAKE_C_FLAGS="/W4" ..
"%VS110COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
