cmake_minimum_required(VERSION 2.8)
project(DisAsm)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" INTERNAL CACHE STRING "limited configs" FORCE)
set(SRC ../../../src)

file(GLOB SOURCES ${SRC}/DisAsm/*.c)
file(GLOB HEADERS ${SRC}/DisAsm/*.h)
add_library(DisAsm ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/StrAsm/*.c)
file(GLOB HEADERS ${SRC}/StrAsm/*.h)
add_library(StrAsm ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/Executable/*.c ${SRC}/Executable/PE/*.c ${SRC}/Executable/MachO/*.c)
file(GLOB HEADERS ${SRC}/Executable/*.h ${SRC}/Executable/PE/*.h ${SRC}/Executable/MachO/*.h)
add_library(Executable ${SOURCES} ${HEADERS})

file(GLOB SOURCES ${SRC}/DisAsmTest/*.c)
file(GLOB HEADERS ${SRC}/DisAsmTest/*.h)
add_executable(DisAsmTest ${SOURCES} ${HEADERS})
target_link_libraries(DisAsmTest DisAsm StrAsm Executable)

file(GLOB SOURCES ${SRC}/DisAsmSample/*.c)
file(GLOB HEADERS ${SRC}/DisAsmSample/*.h)
add_executable(DisAsmSample ${SOURCES} ${HEADERS})
target_link_libraries(DisAsmSample DisAsm StrAsm Executable)
