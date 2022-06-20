//
// Created by krrer on 17.06.22.
//
#include <iostream>
#include <fstream>
#include "include/hamming.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Provide more arguments \n";
        return 0;
    }
    std::fstream readFile, writeFile;
    readFile.open(argv[1], std::fstream::in);
    writeFile.open(argv[2], std::fstream::out);
    int c;
    int p = 0;
    uint8_t tmp = 0;
    int counter = 0;
    while((c = readFile.get()) != EOF){
        tmp = tmp << 4;
        auto a = decode_word((uint8_t)c);
        if( a == 255){
            counter++;
        }
        else
        tmp += a;
        p++;
        if(p == 2){
            p = 0;
            writeFile.write((char*)(&tmp),1);
            tmp =0;
        }
    }
    writeFile.close();
    std::cout << "Number of 2 bit mistakes: " << counter << "\n";
    return 0;
}
