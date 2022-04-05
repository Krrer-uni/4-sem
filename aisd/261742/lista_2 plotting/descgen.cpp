#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char** argv){
    int n;
    istringstream ss(argv[1]);
    ss >> n;
    cout << n << " ";
    for(int i = n -1; i >= 0; i--){
        cout << i << " ";
    }
}