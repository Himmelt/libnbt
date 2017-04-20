cmake_minimum_required(VERSION 3.7)
project(libnbt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/tag_base.cpp src/api/tag_base.h src/api/tag_data.h src/api/tag_vector.h src/api/tag_comp.h src/tag_data.cpp src/tag_vector.cpp src/tag_comp.cpp)
add_library(nbt SHARED ${SOURCE_FILES})

add_executable(main ${SOURCE_FILES})
