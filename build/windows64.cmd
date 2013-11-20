rmdir /s/q windows64
mkdir windows64
copy CMakeLists.txt windows64\CMakeLists.txt
cd windows64
cmake -G "Visual Studio 8 2005 Win64"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com" DisAsm.sln /Build "Release|x64"
cd ..
