//
// Created by krrer on 10.04.2022.
//


#include <bits/stdc++.h>
#include "inc/IntCoding.hpp"
#include "inc/BitWriter.hpp"
#include "inc/IntDecoding.hpp"


int main(){
    int mode = 3;
    auto coder = new IntCoding(mode);
//    auto writer = new BitWriter("test.smoll");
    auto reader = new IntDecoding("test.smoll", mode);
//    for(int i = 1; i < 1000131; i++){
//      writer->write(coder->code(i));
////      std::cout << i << std::endl;
//    }
//    writer->end(mode);
    int n;
    int last_n = 0;
    while((n = reader->nextInt()) != -1){
//        if(n - last_n != 1) std::cout << "error at " << n << std::endl;
        std::cout << n << std::endl;
        last_n = n;
    }
}