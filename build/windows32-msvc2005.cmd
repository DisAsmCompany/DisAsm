rmdir /s/q windows32-msvc2005
mkdir windows32-msvc2005
copy CMakeLists.txt windows32-msvc2005\CMakeLists.txt
cd windows32-msvc2005
cmake -G "Visual Studio 8 2005" -DCMAKE_C_FLAGS="/W4"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|Win32"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
