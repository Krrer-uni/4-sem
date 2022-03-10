#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node{
    int value;
    int position;
    struct Node* next;
    struct Node* previous;
};

void add_element(struct Node** List, int value){
    struct Node* new = malloc(sizeof (struct Node));
    new->next = new;
    new->previous = new;
    new->value = value;
    new->position = 0;
    
    if(*List == NULL){
        *List = new;
    } 
    else {
        new->next = *List;
        new->previous = (*List)->previous;
        (*List)->previous->next = new;
        (*List)->previous = new;
        new->position = new->previous->position +1;
    }
}

struct Node* merge(struct Node ** List1, struct Node ** List2){
    if(*List1 == NULL) return *List2;
    else if(*List2 == NULL) return *List1;
    else {
        int size = (*List1)->previous->position + (*List2)->previous->position +1;
        int start =  (*List1)->previous->position;
        (*List1)->previous->next = *List2;
        (*List2)->previous->next = (*List1);
        struct Node* tmp = (*List2)->previous;
        (*List2)->previous = (*List1)->previous;
        (*List1)->previous = tmp;
        tmp = (*List2);
        for (int i = start +1 ; i < size + 1 ; i++){
            tmp->position = i;
            tmp = tmp->next;
        }
        return *List1;
    }
    
}

int get_value_at(struct Node** List, int position){
    struct Node* tmp = *List;
    int size = (*List)->previous->position;

    if((size/2 >= position)){
        for(int i = 0; i < position; i++){
        tmp = tmp->next;
        
        }
        return tmp->value;
    } else{
        for(int i = 0; i < size - position +1; i++){
            tmp = tmp->previous;
        }
        return tmp->value;
    }

    return tmp->value;
}

int main(int argc, char* argv[]){
    int size = 10000;
    srand(time(NULL));   
    int r = rand()%size;
    clock_t start,end;
    long double cpu_time_used;
    start = clock();
    long double sum = 0;

    // struct Node* LinkedList = NULL;
    // for(int i = 0 ; i < size; i ++){
    //     add_element(&LinkedList, i);
    // }
    // for(int i = 0; i < size; i++){
    //     sum = 0;
    //     for(int j = 0; j < 50; j++){
    //       start = clock();
    //     int tmp = get_value_at(&LinkedList, i);
    //     end = clock();  
    //     sum += ((long double) (end - start)) / CLOCKS_PER_SEC;
    //     }
        
    //     printf("Acces to %d element took: %.8Lf seconds on avarage\n",i,(long double)sum/50);
    // }
    // sum = 0;
    // long double check = 0;
    // for(int i = 0; i < size; i++){
    //     start = clock();
    //     r = rand()%size;
    //     check +=r;
    //     int tmp = get_value_at(&LinkedList,r);
    //     end = clock();
    //     sum += ((long double) ( end - start)) / CLOCKS_PER_SEC;
    // }
    // sum /= size;
    // printf("Acces to random element took: %.10Lf seconds on avarage\n",sum);

      struct Node* MergeList1 = NULL;
    struct Node* MergeList2 = NULL;
    for(int i = 0; i< 10; i++){
        add_element(&MergeList1,i);
        add_element(&MergeList2,i);
    }
    merge(&MergeList1, &MergeList2);
    for(int i = 0; i< 20; i++){
        printf("element of merged list at %d is %d\n",i,get_value_at(&MergeList1, i));
    }
}