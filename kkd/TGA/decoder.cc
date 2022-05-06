//
// Created by krrer on 04.05.22.
//

#include <fstream>
#include "inc/tga.hpp"

class Decoder{
public:
    std::ifstream file;
    Header header;
    explicit Decoder(std::string filename){
        file.open(filename);
        header.idLength = file.get();
    }

};
