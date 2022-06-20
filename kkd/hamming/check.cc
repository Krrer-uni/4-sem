//
// Created by krrer on 17.06.22.
//

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Provide more arguments \n";
    }
    std::fstream readFile1, readFile2;
    readFile1.open(argv[1], std::fstream::in);
    readFile2.open(argv[2], std::fstream::in);
    int c1,c2;
    int p = 0;
    uint8_t tmp = 0;
    int counter = 0;
    while(true){
        c1 = readFile1.get();
        c2 = readFile2.get();
        if(c1 == EOF || c2 == EOF) break;
        if(((uint8_t)c1 & 0b11110000) != ((uint8_t)c2 & 0b11110000)){
            std::cout << c1 << " " << c2 << "\n";
            counter++;
        }
        if(((uint8_t)c1 & 0b00001111) != ((uint8_t)c2 & 0b00001111)){
            std::cout << c1 << " " << c2 << "\n";
            counter++;
        }
    }
    std::cout << "Number of 4 bit block mistakes: " << counter << "\n";
    return 0;
}

