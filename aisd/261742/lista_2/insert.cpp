#include <iostream>
#include <sstream>
using namespace std;

int SWAP = 0;
int COMP = 0;

void swap(int* arr, int a, int b){
    int tmp  = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
    SWAP++;
}

int main(int argc, char** argv){
    int n;
    cin >> n;
    int arr[n];
    
    if(n < 50){
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    
    for(int j = 1; j < n; j++){
        int key = arr[j];
        int i = j -1;
        while(i >= 0 && arr[i] > key){
            COMP++;
            swap(arr,i,i+1);
            i--;
        }
        arr[i+1] = key;
    }
    for(int i = 0; i < n-1; i++){
        if(arr[i]> arr[i+1]){
            cout << "SORTING ERROR\n";
            return -1; 
        }
    }


    if(n < 50){
        for(int i = 0; i < n; i++){
            cin >> arr[i];
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    cout  << COMP << " " << SWAP << "\n";
}