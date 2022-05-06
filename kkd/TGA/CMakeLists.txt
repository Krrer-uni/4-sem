cmake_minimum_required(VERSION 3.22)
project(TGA)

set(CMAKE_CXX_STANDARD 14)

link_directories()

add_executable(TGA main.cpp tga.cc inc/tga.hpp decoder.cc)
    target_link_libraries(TGA ${CMAKE_SOURCE_DIR}/lib/libtga-lib.a)