cmake_minimum_required(VERSION 3.22)
project(vecQuant)

set(CMAKE_CXX_STANDARD 20)

add_executable(vecQuant main.cpp vecQuantlib.cpp tga/tga.h tga/decoder.cpp tga/encoder.cpp)
target_link_libraries(vecQuant ${CMAKE_SOURCE_DIR}/lib/libtga-lib.a)

add_executable(bandCoding bandCoding.cpp tga/tga.h tga/decoder.cpp tga/encoder.cpp)
target_link_libraries(bandCoding ${CMAKE_SOURCE_DIR}/lib/libtga-lib.a)