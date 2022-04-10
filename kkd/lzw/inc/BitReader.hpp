//
// Created by krrer on 09.04.2022.
//


#ifndef LZW_BITREADER_HPP
#define LZW_BITREADER_HPP

#include <bits/stdc++.h>

class BitReader{
public:
    BitReader(std::string filename);

    std::string buffer;
    std::ifstream myfile;
    bool FILE_END;

    unsigned char getChar();

    int getInt();

    char getBit();

    int fillBuffer();
};





#endif //LZW_BITREADER_HPP
