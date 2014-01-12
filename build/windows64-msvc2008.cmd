rmdir /s/q windows64-msvc2008
mkdir windows64-msvc2008
cd windows64-msvc2008
cmake -G "Visual Studio 9 2008 Win64" -DCMAKE_C_FLAGS="/W4" ..
"%VS90COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
Release\DisAsmBenchmark.exe %IPP_HOME%\ipp.bin
cd ..
