rmdir /s/q windows32-msvc2012
mkdir windows32-msvc2012
copy CMakeLists.txt windows32-msvc2012\CMakeLists.txt
cd windows32-msvc2012
cmake -G "Visual Studio 11" -DCMAKE_C_FLAGS="/W4"
"%VS110COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|Win32"
"%VS110COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
