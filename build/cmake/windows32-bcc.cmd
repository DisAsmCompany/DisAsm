mkdir windows32-bcc
copy CMakeLists.txt windows32-bcc\CMakeLists.txt
cd windows32-bcc
cmake -G "Borland Makefiles"
cd ..
