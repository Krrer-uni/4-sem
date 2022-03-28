#include <bits/stdc++.h>

using namespace std;

bool FILE_END = false;

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

Node* makeHuffmanTree(unsigned int* symbols){
    priority_queue<Node*, vector<Node*>, NodeCompare> queue;
    for(int i = 0; i < 256; i++){
        if(symbols[i] > 0){
            // cout << i << " " << symbols[i] <<endl;
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
    
    return root;
}


class BitReader{

    

    public:
    string buffer;
    ifstream myfile;
    unsigned char getChar(){
        int c;
        if((c = myfile.get()) != EOF){
           return (char)c;
        } else return 48;
    }

    int getInt(){
        int out = 0;
        string as_bits = "";
        int c;
        for(int i =0; i< 4; i++){
            out = out<<8;
            c = myfile.get();
            out+=c;
        }
        return out;
    }

    char getBit(){
        if(buffer.size() == 0) fillBuffer();
        unsigned char s = buffer[0];
        buffer.erase(0,1);
        return s;
    }


    int fillBuffer(){
        int c;
        string as_bits = "";
        if((c = myfile.get()) != EOF){
            // cout << c;
            for(int i = 0; i <8; i++){
            as_bits = to_string(c%2) + as_bits;
            c /=2;
            }
            buffer += as_bits;
            return 1;
        } else {
            FILE_END = true;
            return 0;
        }
        
    }

    BitReader(string filename){
        buffer = "";
        myfile.open(filename);
        if(!myfile.is_open()){
        cout << "File with name \"" << filename << "\" couldn't be open" << endl;
        }
    }
};


void setCodes(Node* node, string code, map<char,string>* char_codes){
    if(node == NULL) return;
    if(node->left ==NULL && node->right== NULL){
        // cout << (char)node->symb << " " << code << endl;
        (*char_codes)[node->symb] = code;
        // cout << (*char_codes)[node->symb] << " " << (*char_codes)[node->symb] << endl;
        return;
    } 
    setCodes(node->left, code + "0", char_codes);
    setCodes(node->right, code + "1", char_codes);
}

int main(int argc, char *argv[]){
    unsigned int symbols[256] = {0};
    string filename = argv[1];
    BitReader* reader = new BitReader(filename);

    // int32_t size = reader->getInt();
    int dic_size = reader->getInt();
    int char_count = reader->getInt();
    cout << dic_size << " " << char_count << endl;
    for(int i = 0; i < dic_size; i++){
        // cout << (unsigned int)reader->getChar() << " " << reader->getInt() << endl;
        unsigned char c = reader->getChar();
        int freq = reader->getInt();
        symbols[c] = freq; 
        cout << (unsigned char)c << " " << symbols[c] << endl;
    }
    int k = 0;
    for(int i = 0; i < 256 ; i++){
        if(symbols[i]>0){
        cout << (char)i << " " << symbols[i] << endl;
        k++;
        }
    }

    ofstream  outputFile ("decoded.txt");

    if(dic_size == 1){
        for(int i = 0; i < 256 ; i++){
        if(symbols[i]>0){
            char x = i;
            for(int j = 0; j < char_count; j++){
                outputFile.write(&x,1);
            }
        }
        return 0;
    }
        
    }
    priority_queue<Node*, vector<Node*>, NodeCompare> queue;
    for(int i = 0; i < 256; i++){
        if(symbols[i] > 0){
            cout << i << " " << symbols[i] <<endl;
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



    char c;
    Node * curr = root;
    while((c = reader->getBit()) != 0){
        if(curr->left == NULL && curr->right == NULL){
            outputFile.write(&curr->symb,1);
            curr = root;
        } 
        if(c == '0'){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
}