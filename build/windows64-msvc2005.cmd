rmdir /s/q windows64-msvc2005
mkdir windows64-msvc2005
copy CMakeLists.txt windows64-msvc2005\CMakeLists.txt
cd windows64-msvc2005
cmake -G "Visual Studio 8 2005 Win64" -DCMAKE_C_FLAGS="/W4"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug|x64"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
Release\DisAsmTest.exe
cd ..
