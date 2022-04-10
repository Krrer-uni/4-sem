//
// Created by krrer on 09.04.2022.
//
#include <bits/stdc++.h>
#include <inc/BitReader.hpp>
#include "inc/IntDecoding.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    auto decoding = new IntDecoding(argv[1], 0);

    ofstream write_file(argv[2]);

    map<int, string> dictionary;
    int initial_char = 256;
    for (int i = 0; i < initial_char; i++) {
        char c = (char)i;
        string s;
        s += (char)i;
        dictionary[i] = s;
//        cout << dictionary[i] << endl;
    }
    int word = decoding->nextInt();
    cout << dictionary[word];
    string last_msg = dictionary[word];
    while((word = decoding->nextInt()) != -1){

        if(word == (int)dictionary.size()){
           dictionary[(int)dictionary.size()] = last_msg + last_msg[0];
        } else{
            dictionary[(int)dictionary.size()] = last_msg + dictionary[word][0];
        }
        last_msg = dictionary[word];
//        cout << dictionary[word] << " " << word << endl;
        cout << dictionary[word];
    }

}