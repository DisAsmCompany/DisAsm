rmdir /s/q windows32-msvc2003
mkdir windows32-msvc2003
copy CMakeLists.txt windows32-msvc2003\CMakeLists.txt
cd windows32-msvc2003
cmake -G "Visual Studio 7 .NET 2003" -DCMAKE_C_FLAGS="/W4"
"%VS71COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Debug"
"%VS71COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release"
Release\DisAsmTest.exe
cd ..
