#include <iostream>
#include <sstream>
#include <queue>
#include <random>
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

void merge(int* arr, int  b, int m, int e){
    int i = b;
    int j = m+1;
    int k = 0;
    int arr_out[e-b+1];
    while(i <= m  && j <= e){
        if(ls(arr[i] , arr[j])){
            COMP--;
            arr_out[k] = arr[i];
            
            i++;
        } else{
            arr_out[k] = arr[j];
            j++;
        }
        k++;
        // SWAP++;
    }
    while(i <= m){
        arr_out[k++] = arr[i++];
        // SWAP++;
    }
    while(j <= e){
        arr_out[k++] = arr[j++];
        // SWAP++;
    }
    for(int p = 0; p <= e-b; p++ ){
        arr[p+b] = arr_out[p];
        // SWAP++;
    }
    // if(n < 50){
    //     for(int i = 0; i < n; i++){
    //         cout << arr[i] << " ";
    //     }
    //     cout << "\n";
    // }
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



int partition (int arr[],int low,int high)
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

    // if(n < 50){
    //     for(int i = 0; i < n; i++){
    //         cout << arr[i] << " ";
    //     }
    //     cout << "\n";
    // }
    return p;
}

int randomized_partition(int arr[],int low,int high){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(low, high);
    int i = dist(rng);
    swap(arr,i,low);
    return partition(arr, low, high);
}

int random_select(int arr[], int b, int e, int v){
    if (b == e) return arr[b];
    int r = randomized_partition(arr, b, e);
    int k = r-b + 1;
    if (k == v) return arr[r];
    if (v < k) return random_select(arr,b, r-1, v);
    else return random_select(arr,r+1,e,v-k);
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
    int result = random_select(arr,0,n-1, k);
    

    if(n < 50){
        cout << result << endl;
        for(int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";


        merge_sort(arr,0,n-1);

        for(int i = 0; i < n; i++){
            if(i == k-1){
            cout << "|"<< arr[i] << "| ";;
            } 
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    cout  << COMP << ";" << SWAP << "\n";
}