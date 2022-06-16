//
// Created by krrer on 09.04.2022.
//

#include "include/BitWriter.hpp"

void BitWriter::write(std::string msg) {
    buffer += msg;
    // cout << buffer << endl;
    while (buffer.size() >= 8) {
        char byte = 0;
        for (int i = 0; i < 8; i++) {
            byte = byte << 1;
            byte += ((int) buffer[i] - 48);
        }
        buffer.erase(0, 8);
        myfile.write(&byte, 1);
        BYTES_WRITTEN++;
    }
}

void BitWriter::write(char msg) {
    myfile.write(&msg, 1);
    BYTES_WRITTEN++;
}

void BitWriter::end(int mode) {
    char end_char = '0';
    if(mode == 3 ) end_char = '1';
    char byte = 0;
    while (buffer.size() < 8) buffer += end_char;
    for (int i = 0; i < 8; i++) {
        byte = byte << 1;
        byte += ((int) buffer[i] - 48);
    }
    buffer.erase(0, 8);
    myfile << byte;
    myfile.close();
}

BitWriter::BitWriter(std::string filename) {
    myfile.open(filename);
    buffer = "";
    BYTES_WRITTEN = 0;
}

void BitWriter::write(int msg) {
    if(!(myfile.is_open())) std::cout << "wtf" << std::endl;
    myfile << msg;
    BYTES_WRITTEN+=4;
}
