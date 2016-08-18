cmake_minimum_required(VERSION 3.6)
project(libnbt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp main.cpp src/tag.cpp include/tag.h src/nbt.cpp include/nbt.h)
add_executable(libnbt ${SOURCE_FILES})