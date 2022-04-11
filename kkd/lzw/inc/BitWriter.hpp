//
// Created by krrer on 09.04.2022.
//


#ifndef LZW_BITWRITER_HPP
#define LZW_BITWRITER_HPP

#include <bits/stdc++.h>

class BitWriter {
public:
    std::string buffer;
    std::ofstream myfile;
    int BYTES_WRITTEN;

    void write(std::string msg);

    void write(char msg);
    void write(int msg);
    void end(int mode);

    explicit BitWriter(std::string filename);
};

#endif //LZW_BITWRITER_HPP
