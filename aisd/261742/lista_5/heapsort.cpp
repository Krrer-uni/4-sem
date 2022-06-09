#include "heap.cpp"




    
void heap_sort(int n, int * arr, int &SWAP, int &COMP){
    Heap heap(n);
    heap.build_heap(n,arr);
    for(int i = n-1; i >= 1; i--){
        swap(heap.arr[0],heap.arr[i]);
        heap.size--;
        heap.heapify(0);
    }
    SWAP = heap.SWAP;
    COMP = heap.COMP;
}


int main(int argc, char * argv[]){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(n<50) cout << arr[i] << " ";
    }
    if(n<50) cout << "\n";

    // Heap heap(n);
    // for(int i = 0; i < n; i++){
    //     heap.insert_key(arr[i]);
    //     heap.print();
    // // }
    // heap.build_heap(n,arr);
    // heap.print();
    int SWAP,COMP;
    heap_sort(n,arr, SWAP,COMP);
    // heap.heapify(4);
    // heap.print();
    // for(int i =0; i < n; i ++){
    //     heap.extract_max();
    //     heap.print();
    // }
    
    if(n<50){

        for(int i = 0; i < n; i++){
        cin >> arr[i];
        cout << arr[i] << " ";
    }
    cout << "\n";
    }

    std::cout << SWAP << "," << COMP << endl;
}