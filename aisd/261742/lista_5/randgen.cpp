#include <iostream>
#include <sstream>
#include <random>

using namespace std;

int main(int argc, char** argv){
    int n;
    istringstream ss(argv[1]);
    ss >> n;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(0, 2*n -1);
    cout << n << " ";
    for(int i = 0; i < n; i++){
        cout << dist(rng) << " ";
    }
}