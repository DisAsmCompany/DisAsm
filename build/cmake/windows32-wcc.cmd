mkdir windows32-wcc
copy CMakeLists.txt windows32-wcc\CMakeLists.txt
cd windows32-wcc
cmake -G "Watcom WMake"
cd ..
