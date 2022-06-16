//
// Created by krrer on 17.06.22.
//
#include <iostream>
#include <fstream>
#include "include/hamming.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Provide more arguments \n";
    }
    std::fstream readFile, writeFile;
    readFile.open(argv[1], std::fstream::in);
    writeFile.open(argv[2], std::fstream::out);
    int c;
    while((c = readFile.get()) != EOF){
        decode_word((uint8_t)c);
    }
    writeFile.close();
    return 0;
}
