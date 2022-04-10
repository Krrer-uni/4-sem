#include <bits/stdc++.h>
#include "inc/BitWriter.hpp"
#include "inc/BitReader.hpp"
#include "inc/IntCoding.hpp"

using namespace std;


int main(int argc, char *argv[]) {

    unsigned int symbols[256] = {0};
    unsigned int c;
    unsigned int char_count{0};
    char *filename = argv[1];
    ifstream my_file(filename);
    string write_file_name = filename;
    write_file_name += ".smoll";
    auto coder = new IntCoding(0);

    map<string, int> dictionary;
    int initial_char = 256;
    for (int i = 0; i < initial_char; i++) {
        unsigned char c = i;
        dictionary[string(&c, &c + 1)] = i;
    }

    if (my_file.is_open()) {
        string word = "";
        word += my_file.get();
        auto* writer = new BitWriter(write_file_name);
        while (true) {
            if(dictionary.contains(word)){
                c = my_file.get();
                if(c == EOF){
                    writer->write(coder->code(dictionary[word]));
                    break;
                }
                word += c;
            } else{
                dictionary[word] = (int)dictionary.size();
                cout << word << " " << dictionary[word] << " ";
                writer->write(coder->code(dictionary[word.substr(0,word.size()-1)]));
                word = word.substr(word.size()-1,1);
            }
            symbols[(int) c]++;
        }
        writer->end();
    } else {
        cout << "File with name \"" << filename << "\" couldn't be open" << endl;
        return 0;
    }
}