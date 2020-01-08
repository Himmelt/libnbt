cmake_minimum_required(VERSION 3.7)
project(libnbt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/api/libnbt.h src/libnbt.cpp)
add_library(libnbt SHARED ${SOURCE_FILES})

add_executable(test ${SOURCE_FILES} src/test.cpp)
