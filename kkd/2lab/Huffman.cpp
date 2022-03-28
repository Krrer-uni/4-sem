#include <iostream>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

int BYTES_WRITTEN = 0;

struct Node{
    char symb;
    int symb_freq;

    Node *left, *right;
    Node(char symb, int symb_freq){
        this->symb = symb;
        this->symb_freq = symb_freq;
        left = right = NULL; 
    }
};

class NodeCompare{
    public:
    bool operator()(const Node* left_node, const Node* right_node){
        return (left_node->symb_freq > right_node->symb_freq);
    }
};

class BitWriter{
    public:
    string buffer = "";
    ofstream myfile;

    void write(string msg){
        buffer += msg;
        // cout << buffer << endl;
        while(buffer.size() >= 8){
            char byte = 0;
            for(int i = 0; i< 8; i++){
                byte = byte<<1;
                byte += ((int)buffer[i] - 48);
            }
            buffer.erase(0,8);
            myfile.write(&byte,1);
            BYTES_WRITTEN++;
        }
    }

    void write(char msg){
        myfile.write(&msg,1);
        BYTES_WRITTEN++;
    }

    void end(){
        char byte = 0;
            while(buffer.size() < 8) buffer += '0';
            for(int i = 0; i< 8; i++){
                byte = byte<<1;
                byte += ((int)buffer[i] - 48);
            }
            buffer.erase(0,8);
            myfile << byte;
        myfile.close();
    }

    BitWriter(string filename){
        myfile.open(filename);
    }
};

void setCodes(Node* node, string code, map<char,string>* char_codes){
    if(node == NULL) return;
    if(node->left ==NULL && node->right== NULL){
        (*char_codes)[node->symb] = code;
        return;
    } 
    setCodes(node->left, code + "0", char_codes);
    setCodes(node->right, code + "1", char_codes);
}

map<char,string> makeHuffmanTree(unsigned int* symbols){
    priority_queue<Node*, vector<Node*>, NodeCompare> queue;
    for(int i = 0; i < 256; i++){
        if(symbols[i] > 0){
            queue.push(new Node((char)i, symbols[i]));
        }
    }

    while(queue.size() > 1){
        Node *left =queue.top();
        queue.pop();
        Node *right = queue.top();
        queue.pop();
        Node *fresh = new Node(0, left->symb_freq + right->symb_freq);
        fresh->left = left;
        fresh->right = right;
        queue.push(fresh);
    }
    Node *root =  queue.top();
    map<char,string> char_codes;
    setCodes(root, "", &char_codes);
    
    return char_codes;
}

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

int main (int argc, char* argv[]){
    unsigned int symbols[256] = {0};

    unsigned int c;
    unsigned int char_count{0};

    char* filename = argv[1];
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


    auto char_codes = makeHuffmanTree(symbols);
    BitWriter* writer = new BitWriter("output.bin");

    writer->write(bitset<32>(char_codes.size()).to_string());
    writer->write(bitset<32>(char_count).to_string());

    // cout << char_codes.size() << " " << (int)char_count << endl;
    double code_avg_len = 0;
    for(auto& n : char_codes){
        writer->write((char)n.first);
        writer->write(bitset<32>(symbols[(unsigned char)n.first]).to_string());
        code_avg_len += n.second.size();
    }
        

    myfile.close();
    myfile.open(filename);
    if(myfile.is_open())
        while ((c = myfile.get()) != EOF){
        writer->write(char_codes[(char)c]);
        } 
    else{
        cout << "File with name \"" << filename << "\" couldn't be open" << endl;
        return 0;
    }
    writer->end();
    double encoded_entropy =  entropy("output.bin");
    double compresion_level = (double)char_count/BYTES_WRITTEN;
    code_avg_len /= char_codes.size();
    cout << encoded_entropy << endl;
    cout << code_avg_len << endl;
    cout << compresion_level << endl;


}