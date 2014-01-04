rmdir /s/q windows64-msvc2013
mkdir windows64-msvc2013
cd windows64-msvc2013
cmake -G "Visual Studio 12 Win64" -DCMAKE_C_FLAGS="/W4" ..
"%VS120COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
cd ..
