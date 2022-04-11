//
// Created by krrer on 09.04.2022.
//

#include "inc/IntDecoding.hpp"

int IntDecoding::nextInt() {
    if (mode == 0) {
        return reader->getInt();
    } else if (mode == 1) {
        int n = 1;
        int number = 1;
        char t;

        while ((t = reader->getBit()) != 0) {
            if (t == '0') {
                n++;
                continue;
            }
            if (t == '1') {
                break;
            }
            if (t == 0) return -1;
        }
        while (n > 1) {
            number *= 2;
            if ((t = reader->getBit()) != 0) {
                if (t == '1') {
                    number++;
                }
                n--;
            } else return -1;
        }
        return number - 1;
    } else if (mode == 2) {
        int k = 1;
        int n = 1;
        char t;

        while ((t = reader->getBit()) != 0) {
            if (t == '0') {
                k++;
                continue;
            }
            if (t == '1') {
                break;
            }
            if (t == 0) return -1;
        }
        while (k > 1) {
            n *= 2;
            if ((t = reader->getBit()) != 0) {
                if (t == '1') {
                    n++;
                }
                k--;
            } else return -1;
        }
        int number = 1;
        while (n > 1){
            number *= 2;
            if ((t = reader->getBit()) != 0) {
                if (t == '1') {
                    number++;
                }
                n--;
            } else return -1;
        }
        return number - 1;

    } else if (mode == 3) {
        int n = 1;
        int k = 1;
        char t;
        while((t = reader->getBit()) != 0){
            if(t == '0') return n - 2;
            n = 1;
            while(k > 0){
                if((t = reader->getBit()) != 0){
                    n *=2;
                    if(t=='1') {
                        n++;
                    }
                    k--;
                } else return -1;
            }
            k = n;

        }
        return -1;
    } else if (mode == 4) {
        char t = 'i';
        char last_t;
        int fib_it = 1;
        int number = 0;
        while(true){
            last_t = t;
            if((t = reader->getBit()) != 0){
                if(t == last_t && t == '1'){
                    return number - 1;
                }
                if(t == '1'){
                    number +=fib_lookup[fib_it];
                }
                fib_it++;
            } else return -1;
        }
    }
}


IntDecoding::IntDecoding(std::string filename, int mode) {
    reader = new BitReader(filename);
    this->mode = mode;
    int i = 1;
    int r;
    fib_lookup.push_back(1);
    while(i > 0){
        r = fib_lookup.back();
        fib_lookup.push_back(i);;
        i = r + fib_lookup.back();

    }
}

void IntDecoding::change_mode(int mode) {
    this->mode = mode;
}
