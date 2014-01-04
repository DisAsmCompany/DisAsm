rmdir /s/q windows32-msvc2008
mkdir windows32-msvc2008
copy CMakeLists.txt windows32-msvc2008\CMakeLists.txt
cd windows32-msvc2008
cmake -G "Visual Studio 9 2008" -DCMAKE_C_FLAGS="/W4"
"%VS90COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|Win32"
"%VS90COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
