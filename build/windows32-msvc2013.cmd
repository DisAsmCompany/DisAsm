rmdir /s/q windows32-msvc2013
mkdir windows32-msvc2013
copy CMakeLists.txt windows32-msvc2013\CMakeLists.txt
cd windows32-msvc2013
cmake -G "Visual Studio 12" -DCMAKE_C_FLAGS="/W4"
"%VS120COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|Win32"
"%VS120COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
Release\DisAsmTest.exe
cd ..
