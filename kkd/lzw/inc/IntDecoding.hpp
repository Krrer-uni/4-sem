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
    void change_mode(int mode);

private:
    BitReader *reader;
    int mode;
    std::vector<int> fib_lookup;
};

#endif //LZW_INTDECODING_HPP
