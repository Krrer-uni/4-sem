//
// Created by krrer on 16.06.22.
//

#include "include/bit_operations.hpp"


Eigen::Matrix<int , 8, 1> ctb(uint8_t n) {
    Eigen::Matrix<int , 8, 1> bits;
    uint8_t b = 1;
    for(uint8_t i = 0; i < 8; i++){
        bits[7-i] = (n & b) >> i;
        b = b<<1;
    }
    return bits;
}

uint8_t btc(Eigen::Matrix<int , 8, 1> n) {
    uint8_t byte = 0;
    uint8_t b =1 ;
    for(int i = 0; i < 8 ; i++){
        byte +=  b * n[7-i];
        b = b << 1;
    }
    return byte;
}
