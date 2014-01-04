rmdir /s/q windows32-icc12
mkdir windows32-icc12
copy CMakeLists.txt windows32-icc12\CMakeLists.txt
cd windows32-icc12
if "%PROCESSOR_ARCHITECTURE%"=="AMD64" (set IntelCommon="%CommonProgramFiles(x86)%") else (set IntelCommon="%CommonProgramFiles%")
cmake -G "Visual Studio 8 2005" -DCMAKE_C_FLAGS="/W4"
%IntelCommon%"\Intel\shared files\ia32\Bin\ICProjConvert120.exe" DisAsm.sln /IC
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|Win32"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
