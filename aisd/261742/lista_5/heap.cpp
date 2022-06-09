#include <iostream>


using namespace std;



class Heap{
public:
    int max_size;
    int size;
    int * arr;
    int COMP=0;
    int SWAP=0;

    Heap(int capacity){
        max_size = capacity;
        arr = new (int[max_size]);
        size = 0;
    }
    
    int parent(int i){
        return (i -1)/2;
    }

    int left(int i ){
        return 2*i + 1;
    }

    int right(int i){
        return 2*i + 2;
    }

    void insert_key(int key);
    int extract_max();
    int get_max(){
        return arr[0];
    };
    void decrease_key(int i, int new_val);
    void print();
    void heapify(int i);
    void build_heap(int size, int * arr);
};

void Heap::build_heap(int size, int * arr){
    delete[] this->arr;
    this->arr = arr;
    this->size = size; 
    this->max_size = size;
    int a = 1;
    while(a < size){
        a = 2*a + 1;
    }

    a = (a-1)/2 -1;
    if(size < 50)
        cout << a << endl;
    for(int i = a; i>= 0; i--){
        // print();
        heapify(i);
    }
}

void Heap::heapify(int i){
    while(i < size){
    int l = left(i);
    int r = right(i);
    if(l > size-1)
        break;
    if(r > size -1){
        // cout << arr[l] << " " << arr[i] << endl;
        SWAP++;
        if(arr[i] < arr[l]){
            COMP++;
            swap(arr[l],arr[i]);
        }
        break;
    }
    SWAP++;
    COMP++;
    int m = arr[l] > arr[r] ? arr[l] : arr[r];
    COMP++;
    if(m < arr[i]) break;
    COMP++;
    if(m == arr[l]){
        SWAP++;
        swap(arr[l], arr[i]);
        i = l;
    } else{
        SWAP++;
        swap(arr[r], arr[i]);
        i =r;
    }
    }
}

void Heap::insert_key(int key){
    if(size == max_size) return;
    SWAP++;
    arr[size] = key;
    int i = size;
    size++;
    COMP++;
    while(arr[i] > arr[parent(i)]){
        COMP++;
        SWAP++;
        std::swap(arr[i], arr[parent(i)]);
        i = parent(i);
    }
}

void Heap::print(){
    int a = 1;
    cout << "Heap:" << endl << "[";
    for(int i = 0; i < size; i++){
        if(i == a){

            cout << "]" <<endl << "[";
            a = a * 2 + 1; 
        } 
        cout << arr[i];
        if(i != a-1 && i != size -1){
            cout  << ", ";
        }
        
        
    }
    cout << "]" <<endl;
}

int Heap::extract_max(){
    int max = arr[0];
    SWAP++;
    arr[0] = arr[size-1];
    size--;
    heapify(0);
    
return max;

}
