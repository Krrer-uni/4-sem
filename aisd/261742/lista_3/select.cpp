#include <iostream>
#include <sstream>
#include <queue>
#include <random>
using namespace std;

int SWAP = 0;
int COMP = 0;
int n;
int mts = 5;

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

void insert(int * arr, int low, int high){
    for(int j = low; j < high; j++){
        int key = arr[j];
        int i = j -1;
        while(i >= low && arr[i] > key){
            COMP++;
            swap(arr,i,i+1);
            i--;
        }
        arr[i+1] = key;
        SWAP++;
    }

    // for(int j = low; j < high; j++){
    //     cout << arr[j] << " ";
    // }
    // cout << endl;
    
}

int partition (int arr[],int low,int high, int pivot){
    for(int i = low; i < high; i++){
        COMP++;
        if(arr[i] == pivot){
            swap(arr,i,low);
            break;
        }
    }
        
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
    //     for(int i = low; i <= high; i++){
    //         cout << arr[i] << " ";
    //     }
    //     cout << "\n";
    // }
    return p;
}


int select(int arr[], int b, int e, int v){
   
    if(n < 50){
         cout << "start of select " << v << endl;
        for(int j = b; j < e+1; j++){
        cout << arr[j] << " ";
        }
        cout << "\n";
    }
    
    if(b == e){
        return arr[e];
    } 
    int n_c = (e-b+1);
    int m = (n_c -1)/mts + 1; //(n + mts - 1)/mts
    int m_arr[m];

    // int j = 0;
    // for(int i = b; i <= e;  i+=mts){
    //     if(i + (mts-1) <= e){
    //         insert(arr, i, i+mts);
    //         m_arr[j] = arr[i+((mts-1)/2)];
    //         j++;
    //     }else{
    //         insert(arr,i,e+1);
    //         m_arr[j] = arr[i+((e-i)/2)];
    //     }
    // }
    int i = b;
    int j = 0;
    while(j < m){
        if(i+mts-1 <= e){
            insert(arr,i,i+mts);
            m_arr[j++] = arr[i+(mts)/2];
            SWAP++;
            i+=mts;
        }
        else{
            insert(arr,i,e+1);
            m_arr[j++] = arr[(i+e)/2];
            SWAP++;
        }
    }
    int x = select(m_arr,0,m-1, (m+1)/2);
    int r = partition(arr, b,e,x);
    int k = r - b + 1;
    if (v ==k){
        return x;
    } 
    if(v < k){
        return select(arr,b,r-1,v);
    } 
    else{
        return select(arr,r+1,e,v-k);
    } 
    return -1;
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
    int result = select(arr,0,n-1, k);
   
    
    // cout << partition(arr,0,n-1,4);


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
            else 
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    cout  << COMP << ";" << SWAP << "\n";
}