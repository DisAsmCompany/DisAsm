mkdir windows64
copy CMakeLists.txt windows64\CMakeLists.txt
cd windows64
cmake -G "Visual Studio 8 2005 Win64"
cd ..
