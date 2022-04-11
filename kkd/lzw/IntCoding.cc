//
// Created by krrer on 09.04.2022.
//

#include "inc/IntCoding.hpp"


std::string IntCoding::code(int number) {
    if(mode == 0){
        return std::bitset<32>(number).to_string();
    } else if(mode == 1){
        number++;
        std::string msg = "";
        int n = floor(log2(number) +1 );
        for(int i = 0; i < n - 1; i++){
            msg += "0";
        }
        std::string bitwise = std::bitset<32>(number).to_string();
        int first_one = bitwise.find_first_of('1');
        msg += bitwise.substr(first_one);
//        std::cout << msg;
        return msg;
    } else if(mode == 2){
        number++;
        std::string msg = "";
        int n = floor(log2(number) + 1);
        int k = floor(log2(n) + 1);
        for(int i = 0; i < k - 1; i++){
            msg += "0";
        }
        std::string bitwise = std::bitset<32>(n).to_string();
        int first_one = bitwise.find_first_of('1');
        msg += bitwise.substr(first_one);
        bitwise = std::bitset<32>(number).to_string();
        first_one = bitwise.find_first_of('1');
        msg += bitwise.substr(first_one +1);
//        std::cout << msg;
        return msg;
    } else if(mode ==3){
        number++;
        number++;
        std::string msg = "0";
        int k = number;
        while(k > 1){
            std::string bitwise = std::bitset<32>(k).to_string();
            int first_one = bitwise.find_first_of('1');
            msg = bitwise.substr(first_one) + msg;
            k = floor(log2(k) + 1) - 1;
        }
        return msg;

    } else if(mode ==4){
        number++;
        while(number >= fib_lookup.back()){
            fib_lookup.push_back(fib_lookup.back() + fib_lookup[fib_lookup.size()-2]);
        }
        std::string msg = "";
        int n = 1;
        while(number >= fib_lookup[n]){
            n++;
        }
        n--;
        while(n > 0){
            if(number >= fib_lookup[n]){
                number -= fib_lookup[n];
                msg = '1' + msg;
            } else{
                msg = '0' + msg;
            }
            n--;
        }
        msg +='1';
        return msg;
    }
    return "0";

}

IntCoding::IntCoding(int mode) {
        this->mode = mode;
        fib_lookup.push_back(1);
        fib_lookup.push_back(1);
}
