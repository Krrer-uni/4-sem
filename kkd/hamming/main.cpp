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
    uint8_t dict[16];
    generate_dict(dict,16);
    int c;
    while((c = readFile.get()) != EOF){
        uint8_t first = ((uint8_t)c & 0b11110000) >> 4;
        uint8_t second = (uint8_t)c & 0b00001111;
        std:: cout << (int)first << " " << (int)second << "\n";
        writeFile.write((char*)(&dict[first]), 1);
        writeFile.write((char*)(&dict[second]), 1);
    }
    writeFile.close();
    return 0;
}
