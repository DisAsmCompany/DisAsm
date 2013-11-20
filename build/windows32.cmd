rmdir /s/q windows32
mkdir windows32
copy CMakeLists.txt windows32\CMakeLists.txt
cd windows32
cmake -G "Visual Studio 8 2005"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.com" DisAsm.sln /Build "Release|Win32"
cd ..
