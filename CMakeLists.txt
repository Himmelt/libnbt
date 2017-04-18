cmake_minimum_required(VERSION 3.7)
project(libnbt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/tag_base.h src/tag_data.h src/tag_type.h src/main.cpp)
add_library(nbt SHARED ${SOURCE_FILES})

add_executable(main ${SOURCE_FILES})