rmdir /s/q windows32-msvc6
mkdir windows32-msvc6
copy CMakeLists.txt windows32-msvc6\CMakeLists.txt
cd windows32-msvc6
cmake -G "Visual Studio 6" -DCMAKE_C_FLAGS="/W4 /Zm200"
"%VS60COMNTOOLS%\..\MSDev98\Bin\msdev.exe" DisAsm.dsw /MAKE ALL
Release\DisAsmTest.exe
cd ..
