#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char** argv){
    int n;
    istringstream ss(argv[1]);
    ss >> n;
    cout << n << " ";
    for(int i = 0; i < n; i++){
        cout << i << " ";
    }
}