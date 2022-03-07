#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


int main (int argc, char* argv[]){
    unsigned int symbols[256] = {0};
    unsigned int consecutive_symbols[256*256] = { 0 };

    unsigned int c;
    unsigned int last_c = 0;
    unsigned int char_count{0};

    char* filename = argv[1];
    ifstream myfile (filename);

    if(myfile.is_open())
        while ((c = myfile.get()) != EOF){
        symbols[(int)c]++;
        consecutive_symbols[(int)c + 256*last_c]++;
        char_count++;
        last_c = c;
        } 
    else{
        cout << "File with name \"" << filename << "\" couldn't be open" << endl;
        return 0;
    }

    double result = -0;
    double log_count = log2((double)char_count);
    for(int i =0 ; i < 256; i++){
        if(symbols[i] > 0){
            result += (double)symbols[i] * (log2((double)symbols[i]) - log_count);
        }
    }
    result = -result;
    result /= (double)char_count;
    cout << result << endl;

    result = -0;
    for(int i =0; i < 256; i++){
        if(symbols[i] > 0){
            log_count = log2((double)symbols[i]);
            for(int j = 0; j < 256; j++){
                if(consecutive_symbols[j + 256*i] > 0){
                    result += (double)consecutive_symbols[j + 256*i] * (log2((double)consecutive_symbols[j + 256*i]) - log_count);
                }
            }
        }
    }
    result = -result;
    result /= (double)char_count;
    cout << result << endl;
}