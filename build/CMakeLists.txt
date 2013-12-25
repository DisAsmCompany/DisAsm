cmake_minimum_required(VERSION 2.8)
project(DisAsm)

set(SRC ../../src)

file(GLOB SOURCES ${SRC}/DisAsm/*.c)
file(GLOB HEADERS ${SRC}/DisAsm/*.h)
add_library(DisAsm ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/DisAsmPlatform/*.c)
file(GLOB HEADERS ${SRC}/DisAsmPlatform/*.h)
add_library(DisAsmPlatform ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/StrAsm/*.c)
file(GLOB HEADERS ${SRC}/StrAsm/*.h)
add_library(StrAsm ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/Executable/*.c)
file(GLOB HEADERS ${SRC}/Executable/*.h)
add_library(Executable ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/Executable/PE/*.c)
file(GLOB HEADERS ${SRC}/Executable/PE/*.h)
add_library(PluginFormatPE ${SOURCES} ${HEADERS})
target_link_libraries(PluginFormatPE Executable)
add_dependencies(PluginFormatPE Executable)

file(GLOB SOURCES ${SRC}/Executable/NE/*.c)
file(GLOB HEADERS ${SRC}/Executable/NE/*.h)
add_library(PluginFormatNE ${SOURCES} ${HEADERS})
target_link_libraries(PluginFormatNE Executable)
add_dependencies(PluginFormatNE Executable)

file(GLOB SOURCES ${SRC}/Executable/LX/*.c)
file(GLOB HEADERS ${SRC}/Executable/LX/*.h)
add_library(PluginFormatLX ${SOURCES} ${HEADERS})
target_link_libraries(PluginFormatLX Executable)
add_dependencies(PluginFormatLX Executable)

file(GLOB SOURCES ${SRC}/Executable/ELF/*.c)
file(GLOB HEADERS ${SRC}/Executable/ELF/*.h)
add_library(PluginFormatELF ${SOURCES} ${HEADERS})
target_link_libraries(PluginFormatELF Executable)
add_dependencies(PluginFormatELF Executable)

file(GLOB SOURCES ${SRC}/Executable/MachO/*.c)
file(GLOB HEADERS ${SRC}/Executable/MachO/*.h)
add_library(PluginFormatMachO ${SOURCES} ${HEADERS})
target_link_libraries(PluginFormatMachO Executable)
add_dependencies(PluginFormatMachO Executable)

file(GLOB SOURCES ${SRC}/DisAsmTest/*.c)
file(GLOB HEADERS ${SRC}/DisAsmTest/*.h)
add_executable(DisAsmTest ${SOURCES} ${HEADERS})
target_link_libraries(DisAsmTest DisAsm DisAsmPlatform StrAsm Executable PluginFormatPE PluginFormatNE PluginFormatLX PluginFormatELF PluginFormatMachO)
add_dependencies(DisAsmTest DisAsm DisAsmPlatform StrAsm Executable PluginFormatPE PluginFormatNE PluginFormatLX PluginFormatELF PluginFormatMachO)

file(GLOB SOURCES ${SRC}/DisAsmSample/*.c)
file(GLOB HEADERS ${SRC}/DisAsmSample/*.h)
add_executable(DisAsmSample ${SOURCES} ${HEADERS})
target_link_libraries(DisAsmSample DisAsm DisAsmPlatform StrAsm Executable PluginFormatPE PluginFormatNE PluginFormatLX PluginFormatELF PluginFormatMachO)
add_dependencies(DisAsmSample DisAsm DisAsmPlatform StrAsm Executable PluginFormatPE PluginFormatNE PluginFormatLX PluginFormatELF PluginFormatMachO)

file(GLOB SOURCES ${SRC}/DisAsmBenchmark/*.c)
file(GLOB HEADERS ${SRC}/DisAsmBenchmark/*.h)
add_executable(DisAsmBenchmark ${SOURCES} ${HEADERS})
target_link_libraries(DisAsmBenchmark DisAsm DisAsmPlatform)
add_dependencies(DisAsmBenchmark DisAsm DisAsmPlatform)

file(GLOB SOURCES ${SRC}/SDK/SampleRAW/*.c)
file(GLOB HEADERS ${SRC}/SDK/SampleRAW/*.h)
add_executable(SampleRAW ${SOURCES} ${HEADERS})
target_link_libraries(SampleRAW DisAsm DisAsmPlatform StrAsm)
add_dependencies(SampleRAW DisAsm DisAsmPlatform StrAsm)

file(GLOB SOURCES ${SRC}/SDK/SampleSSE/*.c)
file(GLOB HEADERS ${SRC}/SDK/SampleSSE/*.h)
add_executable(SampleSSE ${SOURCES} ${HEADERS})
target_link_libraries(SampleSSE DisAsm DisAsmPlatform StrAsm)
add_dependencies(SampleSSE DisAsm DisAsmPlatform StrAsm)

if(BUILD_GUI)

file(GLOB SOURCES ${SRC}/DisAsmGUI/*.c)
file(GLOB HEADERS ${SRC}/DisAsmGUI/*.h)
add_executable(DisAsmGUI ${SOURCES} ${HEADERS})
target_link_libraries(DisAsmGUI DisAsm DisAsmPlatform StrAsm Executable PluginFormatPE PluginFormatNE PluginFormatLX PluginFormatELF PluginFormatMachO)
add_dependencies(DisAsmGUI DisAsm DisAsmPlatform StrAsm Executable PluginFormatPE PluginFormatNE PluginFormatLX PluginFormatELF PluginFormatMachO)

endif(BUILD_GUI)