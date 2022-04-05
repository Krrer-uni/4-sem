#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

int SWAP = 0;
int COMP = 0;

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

void merge(int* arr, int  b, int m, int e){
    int i = b;
    int j = m+1;
    int k = 0;
    int arr_out[e-b+1];
    while(i <= m  && j <= e){
        if(ls(arr[i] , arr[j])){
            arr_out[k] = arr[i];
            i++;
        } else{
            arr_out[k] = arr[j];
            j++;
        }
        k++;
    }
    while(i <= m){
        arr_out[k++] = arr[i++];
    }
    while(j <= e){
        arr_out[k++] = arr[j++];
    }
    for(int p = 0; p <= e-b; p++ ){
        arr[p+b] = arr_out[p];
    }
}

void merge_sort(int arr[], int b, int e){
    if(b==e) return;
    else{
        int m = b + (e-b)/2;
        merge_sort(arr, b, m );
        merge_sort(arr, m +1, e);
        merge(arr,b, m, e );
    }
}

int main(int argc, char** argv){
    int n;
    cin >> n;
    int arr[n];

    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(n<50) cout << arr[i] << " ";
    }
    if(n<50) cout << "\n";
    
    // int test[6] = { 6, 5, 4, 3, 2, 1};
    merge_sort(arr,0,n-1);


    for(int i = 0; i < n-1; i++){
        if(arr[i]> arr[i+1]){
            cout << "SORTING ERROR\n";
            return -1; 
        }
    }


    if(n < 50){
        for(int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    cout  << COMP << " " << SWAP << "\n";
}