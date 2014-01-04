rmdir /s/q windows64-icc12
mkdir windows64-icc12
cd windows64-icc12
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (set IntelCommon="%CommonProgramFiles(x86)%") else (set IntelCommon="%CommonProgramFiles%")
cmake -G "Visual Studio 8 2005 Win64" -DCMAKE_C_FLAGS="/W4" .
%IntelCommon%"\Intel\shared files\ia32\Bin\ICProjConvert120.exe" DisAsm.sln /IC
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
cd ..
