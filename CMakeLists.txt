cmake_minimum_required(VERSION 3.7)
project(libnbt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/tag.cpp src/include/tag.h)
add_library(nbt SHARED ${SOURCE_FILES})
