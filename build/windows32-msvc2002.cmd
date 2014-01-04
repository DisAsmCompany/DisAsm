rmdir /s/q windows32-msvc2002
mkdir windows32-msvc2002
cd windows32-msvc2002
cmake -G "Visual Studio 7" -DCMAKE_C_FLAGS="/W4" ..
"%VS70COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release"
Release\DisAsmTest.exe
cd ..
