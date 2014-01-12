rmdir /s/q windows64-icc14
mkdir windows64-icc14
cd windows64-icc14
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (set IntelCommon="%CommonProgramFiles(x86)%") else (set IntelCommon="%CommonProgramFiles%")
cmake -G "Visual Studio 9 2008 Win64" -DCMAKE_C_FLAGS="/W4" ..
%IntelCommon%"\Intel\shared files\ia32\Bin\ICProjConvert140.exe" DisAsm.sln /IC
"%VS90COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
Release\DisAsmBenchmark.exe %IPP_HOME%\ipp.bin
cd ..
