#include "heap.cpp"





int main(int argc, char * argv[]){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(n<50) cout << arr[i] << " ";
    }
    if(n<50) cout << "\n";

    Heap heap(n);
    for(int i = 0; i < n; i++){
        heap.insert_key(arr[i]);
        if( n < 50)
        heap.print();
    }
    for(int i =0; i < n; i ++){
        heap.extract_max();
        if(n < 50)
        heap.print();
    }
    std::cout << heap.SWAP << ";" << heap.COMP << endl;
    // if(n<50){

    //     for(int i = 0; i < n; i++){
    //     cin >> arr[i];
    //     cout << arr[i] << " ";
    // }
    // cout << "\n";
    // }

}