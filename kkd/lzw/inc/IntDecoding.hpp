//
// Created by krrer on 09.04.2022.
//

#ifndef LZW_INTDECODING_HPP
#define LZW_INTDECODING_HPP

#include <bits/stdc++.h>
#include <inc/BitReader.hpp>

class IntDecoding{
public:
    int nextInt();
    explicit IntDecoding(std::string filename, int mode);

private:
    BitReader *reader;
    int mode;
};

#endif //LZW_INTDECODING_HPP
