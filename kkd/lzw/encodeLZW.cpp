#include <bits/stdc++.h>
#include "inc/BitWriter.hpp"
#include "inc/BitReader.hpp"
#include "inc/IntCoding.hpp"

using namespace std;


double entropy(string filename){
    unsigned int symbols[256] = {0};
    unsigned int c;
    unsigned int char_count{0};
    ifstream myfile (filename);
    if(myfile.is_open())
        while ((c = myfile.get()) != EOF){
            symbols[(int)c]++;
            char_count++;
        }
    else{
        cout << "File with name \"" << filename << "\" couldn't be open" << endl;
        return 0;
    }

    double entryFileEntropy = 0;
    double log_count = log2((double)char_count);
    for(int i =0 ; i < 256; i++){
        if(symbols[i] > 0){
            entryFileEntropy += (double)symbols[i] * (log2((double)symbols[i]) - log_count);
        }
    }
    entryFileEntropy = -entryFileEntropy;
    entryFileEntropy /= (double)char_count;
    // cout << entryFileEntropy << endl;
    return entryFileEntropy;
}


int main(int argc, char *argv[]) {

    unsigned int symbols[256] = {0};
    int c;
    int char_count{0};
    int char_writter;
    char *filename = argv[1];
    int codingMode = stoi(argv[2]);
    ifstream my_file(filename);
    string write_file_name = filename;
    write_file_name += ".smoll";
    auto coder = new IntCoding(codingMode);

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
        writer->write(std::bitset<32>(codingMode).to_string());
        while (true) {
            if(dictionary.contains(word)){
                c = my_file.get();
                char_count++;
                if(c == EOF){
                    writer->write(coder->code(dictionary[word]));
                    break;
                }
                word += c;
            } else{
                dictionary[word] = (int)dictionary.size();
//                cout << dictionary[word.substr(0,word.size()-1)]<< endl;
                writer->write(coder->code(dictionary[word.substr(0,word.size()-1)]));
                word = word.substr(word.size()-1,1);
            }
            symbols[(int) c]++;
        }
        writer->end(codingMode);
        char_writter = writer->BYTES_WRITTEN;
    } else {
        cout << "File with name \"" << filename << "\" couldn't be open" << endl;
        return 0;
    }

    cout << char_count << endl;
    cout << char_writter << endl;
    cout << entropy(argv[1]) << endl;
    cout << entropy(write_file_name) << endl;
}