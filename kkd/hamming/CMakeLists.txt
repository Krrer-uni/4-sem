cmake_minimum_required(VERSION 3.22)
project(hamming)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(hamming main.cpp hamming.cc  bit_operations.cc  BitReader.cc
        BitWriter.cc)
add_executable(noise noise.cc )

add_executable(decode decode.cc hamming.cc  bit_operations.cc  BitReader.cc
        BitWriter.cc)