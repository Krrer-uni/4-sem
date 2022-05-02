#include <iostream>
#include <sstream>
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


void partition (int arr[],int low,int high, int* lp, int* rp, int x, int y)
{
    // cout << "in:" << endl;
    // for(int i = 0; i < n; i++){
    //     cout << arr[i] << " ";
    //     }
    // cout << "\n";
     for(int i = low; i < high; i++){
        COMP++;
        if(arr[i] == x){
            swap(arr,i,low);
            continue;
        }
        if(arr[i] == y){
            swap(arr,i,high);
            continue;
        }
    }
        
    if(ls(arr[high],arr[low])) swap(arr,high,low);
    int p = arr[high];  
    int q = arr[low];
    SWAP+=2;

    // cout << "p = " << p << " q = " << q << " low = " << low << " high = " << high << endl;
 
    int l = (low);
    int h = (high);

    for (int j = low + 1; j < h; j++)
    {
        if (l - low < high - h)
        {
            if(ls(arr[j], q)){
                l++;
                swap(arr,j,l);
            } else if(ls( p , arr[j])){
                h--;
                swap(arr,j,h);
                j--;
            } 
        } else {
            if(ls( p , arr[j])){
                h--;
                swap(arr,j,h);
                j--;
            } else if(ls(arr[j], q)){
                l++;
                swap(arr,j,l);
            } 
        }
    }
    swap(arr, h ,high);
    swap(arr, l ,low);
    *lp = l;
    *rp = h;

    // cout << "out:" << endl;
    // for(int i = 0; i < 10; i++){
    //     cout << arr[i] << " ";
    //     }
    // cout << "\n";
}

void quick(int arr[], int b, int e){
    if (b < e){
        int p,l;
        int x = select(arr,b,e,(e-b)/3+1);
        int y = select(arr,b,e,(e-b)*2/3+1);
        partition(arr,b,e, &l, &p,x,y);
        // cout << l << " " << p << endl;
        quick(arr,b,l-1);
        quick(arr,l+1,p-1);
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