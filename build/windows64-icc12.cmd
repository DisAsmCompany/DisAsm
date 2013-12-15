rmdir /s/q windows64-icc12
mkdir windows64-icc12
copy CMakeLists.txt windows64-icc12\CMakeLists.txt
cd windows64-icc12
cmake -G "Visual Studio 8 2005 Win64" -DCMAKE_C_FLAGS="/W4"
"%CommonProgramFiles%\Intel\shared files\ia32\Bin\ICProjConvert120.exe" DisAsm.sln /IC
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|x64"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
cd ..
