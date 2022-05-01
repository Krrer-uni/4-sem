#include <iostream>
#include <sstream>
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

int partition(int arr[],int low,int high)
{
    int pivot = arr[low];  
    SWAP++;
 
    int p = low;

    for (int j = p+1; j <= high; j++)
    {
        if (ls(arr[j] , pivot))
        {
            p++;
            swap(arr, p ,j);
        }
    }
    swap(arr, p  ,low);

    if(n < 50){
        for(int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    return p;
}

void quick(int arr[], int b, int e){
    if (b < e){
        int p = partition(arr,b,e);
        quick(arr,b,p-1);
        quick(arr,p+1,e);
    }
}

int main(int argc, char** argv){
    cin >> n;
    int arr[n];
    
    
    for(int i = 0; i < n; i++){
        cin >> arr[i];
       if(n < 50) cout << arr[i] << " ";
    }
    if(n < 50) cout << "\n";
    
    
    quick(arr,0,n-1);

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
    cout  << COMP << ";" << SWAP << "\n";
}