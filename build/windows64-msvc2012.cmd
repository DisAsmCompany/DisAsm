rmdir /s/q windows64-msvc2012
mkdir windows64-msvc2012
cd windows64-msvc2012
cmake -G "Visual Studio 11 Win64" -T "v110_xp" -DCMAKE_C_FLAGS="/W4" ..
"%VS110COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
cd ..
