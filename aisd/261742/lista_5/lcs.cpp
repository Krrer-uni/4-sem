#include <iostream>
#include <array>
#include <time.h>

int SWAP =0;
int COMP = 0;

template <class T>
T* lcs (T * A, int a_size, T* B, int b_size,int &out_size){
    int m = a_size;
    int n = b_size;
    int** arr = new int*[m];
    for(int i = 0; i < m; ++i)
        arr[i] = new int[n];
    COMP++;
    int s = (A[0] == B[0]);
    for(int a = 0; a < m;a++){
        for(int b = 0; b < m; b++){
            SWAP++; 
            arr[a][b] = 0;
        }
    }
    for(int i = 0;i<m; i++){
        arr[i][0] = s;
        SWAP++;
    }
    for(int i = 0;i<n; i++){
        arr[0][i] = s;
        SWAP++;
    }
    int tmp;
    for(int a = 1; a < m;a++){
        for(int b = 1; b < m; b++){
            tmp = 0;
            COMP++;
            if(A[a] == B[b]){
                SWAP++;
                tmp = arr[a-1][b-1] +1; 
            }
            SWAP++;
            COMP+=2;
            arr[a][b] = std::max(std::max(arr[a-1][b],arr[a][b-1]),tmp);
            
        }
    }
    s = arr[m-1][n-1];
    out_size =s;
    T* sol = (T*)std::malloc(sizeof(T) * s--);
    int i = 0;
    int a = m-1;
    int b = n-1;
    if(n < 20){
        std::cout << s << "\n";
        for(int a = 0; a < m;a++){
            for(int b = 0; b < m; b++){
                std::cout  << arr[a][b] << " ";
            }
            std::cout << "\n";
        }
    }
    while(a > 0 && b > 0){
        COMP++;
        if(arr[a][b] == arr[a-1][b]){
            a--;
            continue;
        }
        COMP++;
        if(arr[a][b] == arr[a][b-1]){
            b--;
            continue;
        }
        SWAP++;
        sol[s--] = A[a];
        a--;
        b--;
    }
    COMP++;
    if(arr[a][b] > 0){
        SWAP++;
        sol[s] = A[a];
    }
    return sol;
}


int main(int argc, char* argv[]){
    int n = std::stoi(argv[1]);
   srand (time(NULL));
    // int n = 10;
    int range = std::stoi(argv[2]);
    int A[n];
    int B[n];
    for (int i =0; i < n; i++){
        A[i] = rand()%range;
        B[i] = rand()%range;
    }
;
    if(n < 20){
    for(int i = 0; i < n; i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << B[i] << " ";
    }
    std::cout << std::endl;
    }
    int s;

    int *LCS = lcs(A,n,B,n,s);

    if(n < 20){
        for(int i = 0 ; i < s ;i++){
            std::cout << LCS[i] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << SWAP <<  ";" <<  COMP << std::endl;
}