rmdir /s/q windows32-icc14
mkdir windows32-icc14
cd windows32-icc14
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (set IntelCommon="%CommonProgramFiles(x86)%") else (set IntelCommon="%CommonProgramFiles%")
cmake -G "Visual Studio 9 2008" -DCMAKE_C_FLAGS="/W4" ..
%IntelCommon%"\Intel\shared files\ia32\Bin\ICProjConvert140.exe" DisAsm.sln /IC
"%VS90COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
