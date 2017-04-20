cmake_minimum_required(VERSION 3.7)
project(libnbt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/tag_base.h src/tag_data.h src/main.cpp src/tag_vector.h)
add_library(nbt SHARED ${SOURCE_FILES})

add_executable(main ${SOURCE_FILES} src/tag_comp.h src/tag.h)