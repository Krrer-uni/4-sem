//
// Created by krrer on 09.04.2022.
//

#include "inc/BitReader.hpp"

unsigned char BitReader::getChar() {
    int c;
    if ((c = myfile.get()) != EOF) {
        return (char) c;
    } else return 48;
}

int BitReader::getInt() {
    int out = 0;
    std::string as_bits;
    int c;
    for (int i = 0; i < 4; i++) {
        out = out << 8;
        c = myfile.get();
        if(c == EOF) return -1;
        out += c;
    }
    return out;
}

char BitReader::getBit() {
    if (buffer.size() == 0) fillBuffer();
    unsigned char s = buffer[0];
    buffer.erase(0, 1);
    return s;
}


int BitReader::fillBuffer() {
    int c;
    std::string as_bits = "";
    if ((c = myfile.get()) != EOF) {
        // cout << c;
        for (int i = 0; i < 8; i++) {
            as_bits = std::to_string(c % 2) + as_bits;
            c /= 2;
        }
        buffer += as_bits;
        return 1;
    } else {
        FILE_END = true;
        return 0;
    }

}

BitReader::BitReader(std::string filename) {
    buffer = "";
    myfile.open(filename);
    if (!myfile.is_open()) {
        std::cout << "File with name \"" << filename << "\" couldn't be open" << std::endl;
    }
    FILE_END = false;
}
