cmake_minimum_required(VERSION 3.21)
project(lzw)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(encode
        encodeLZW.cpp inc/BitWriter.hpp BitWriter.cc BitReader.cc inc/BitReader.hpp IntCoding.cc inc/IntCoding.hpp )
add_executable(decode
        decodeLZW.cc BitReader.cc inc/BitReader.hpp IntCoding.cc inc/IntCoding.hpp inc/IntDecoding.hpp IntDecoding.cc)