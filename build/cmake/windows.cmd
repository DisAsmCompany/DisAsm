mkdir windows
copy CMakeLists.txt windows\CMakeLists.txt
cd windows
cmake -G "Visual Studio 8 2005"
cd ..
