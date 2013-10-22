mkdir windows32
copy CMakeLists.txt windows32\CMakeLists.txt
cd windows32
cmake -G "Visual Studio 8 2005"
cd ..
