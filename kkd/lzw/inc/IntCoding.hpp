//
// Created by krrer on 09.04.2022.
//

#ifndef LZW_INTCODING_HPP
#define LZW_INTCODING_HPP

#include <bits/stdc++.h>

class IntCoding {


public:
    IntCoding(int mode);

    std::string code(int number);

private:
    int mode;
    std::vector<int> fib_lookup;
};


#endif //LZW_INTCODING_HPP
