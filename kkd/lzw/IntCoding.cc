//
// Created by krrer on 09.04.2022.
//

#include "inc/IntCoding.hpp"


std::string IntCoding::code(int number) {
    if(mode == 0){
        return std::bitset<32>(number).to_string();
    } else return "";
}

IntCoding::IntCoding(int mode) {
        this->mode = mode;
}
