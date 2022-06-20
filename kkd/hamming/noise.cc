//
// Created by krrer on 17.06.22.
//
#include <iostream>
#include <fstream>
#include <random>
int main(int argc, char* argv[]) {
    if(argc < 3){
        std::cout << "Provide more arguments \n";
    }
    std::fstream readFile, writeFile;
    double p = std::stod(argv[1]);
    readFile.open(argv[2], std::fstream::in);
    writeFile.open(argv[3], std::fstream::out);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    int c;
    int counter =0;
    while((c = readFile.get()) != EOF){
        for(int i = 1; i <= 128 ; i*=2){
            if(dis(rd) < p){
                c = c ^ i;
                counter ++;
            }
        }
        writeFile.write((char*)&c, 1);
    }
    writeFile.close();
    std::cout << "bits flipped: " << counter << "\n";
    return 0;
}
