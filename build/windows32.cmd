rmdir /s/q windows32
mkdir windows32
copy CMakeLists.txt windows32\CMakeLists.txt
cd windows32
cmake -G "Visual Studio 8 2005" -DCMAKE_C_FLAGS="/W4"
"%VS80COMNTOOLS%\..\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
cd ..
