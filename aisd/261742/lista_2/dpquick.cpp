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

int ls(int a, int b){
    COMP++;
    return a < b;
}

void partition (int arr[],int low,int high, int* lp, int* rp)
{
    if(ls(arr[high],arr[low])) swap(arr,high,low);
    int p = arr[high];  
    int q = arr[low];
 
    int l = (low);
    int h = (high);

    for (int j = low + 1; j < h; j++)
    {
        if (l - low < high - h)
        {
            if(arr[j] < q){
                l++;
            } else if(arr[j]>p){
                h--;
                swap(arr[j],arr[h]);
            } 
        }
    }
    swap(arr, h ,high);
    swap(arr, l ,low);
    *lp = l;
    *rp = h;
}

void quick(int arr[], int b, int e){
    if (b < e){
        int p,l;
        partition(arr,b,e, &l, &p);
        quick(arr,b,l-1);
        quick(arr,l+1,p-1);
        quick(arr,p+1,e);
    }
}

int main(int argc, char** argv){
    int n;
    cin >> n;
    int arr[n];
    
    
    for(int i = 0; i < n; i++){
        cin >> arr[i];
       if(n < 50) cout << arr[i] << " ";
    }
    if(n < 50) cout << "\n";
    
    
    quick(arr,0,n-1);

    // for(int i = 0; i < n-1; i++){
    //     if(arr[i]> arr[i+1]){
    //         cout << "SORTING ERROR\n";
    //         return -1; 
    //     }
    // }


    if(n < 50){
        for(int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    cout  << COMP << " " << SWAP << "\n";
}