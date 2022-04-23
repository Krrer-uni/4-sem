#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

int SWAP = 0;
int COMP = 0;
int n;

void swap(int* arr, int a, int b){
    int tmp  = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
    SWAP++;
}

int ls(int a, int b){
    COMP++;
    return a < b;
}


int binary_search(int arr[], int b, int e, int v){
    int c = (e+b)/2;
    if(n < 50){
        for(int i = b; i < e+1; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    
    if(ls(v,c)) return binary_search(arr, b, c-1 ,v);
    if(ls(c,v)) return binary_search(arr, c +1, e,v);
    if(c==v) return 1;
    if(b==e) return 0;
    return 0;
}

int main(int argc, char** argv){
    int k;
    cin >> n;
    int arr[n];
    cin >> k;

    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(n<50) cout << arr[i] << " ";
    }
    if(n<50) cout << "\n";
    
    // int test[6] = { 6, 5, 4, 3, 2, 1};
    binary_search(arr,0,n-1, k);


    for(int i = 0; i < n-1; i++){
        if(arr[i]> arr[i+1]){
            cout << "SORTING ERROR\n";
            return -1; 
        }
    }


    // if(n < 50){
    //     for(int i = 0; i < n; i++){
    //         cout << arr[i] << " ";
    //     }
    //     cout << "\n";
    // }
    cout  << COMP << ";" << SWAP << "\n";
}