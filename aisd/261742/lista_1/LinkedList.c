#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node{
    int value;
    struct Node* next;
};

void add_element(struct Node** List, int value){
    struct Node* new = malloc(sizeof (struct Node));
    new->next = NULL;
    new->value = value;
    
    if(*List == NULL){
        *List = new;
    } else if((*List)->next ==NULL){
        (*List)->next = new;
    } else {
        struct Node* tmp = *List;
        while (tmp->next->next != NULL) tmp = tmp->next;  
        tmp->next->next = new;
    }
}

int get_value_at(struct Node** List, int position){
    struct Node* tmp = *List;
    for(int i = 0; i < position; i++){
        if(tmp->next == NULL)   return -1;
        tmp = tmp->next;
    }
    return tmp->value;
}

struct Node* merge(struct Node ** List1, struct Node ** List2){
    
    struct Node* tmp = *List1;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = *List2;
    return *List1;
}

int main(int argc, char* argv[]){
    int size = 1000;
    srand(time(NULL));   
    int r = rand()%size;
    clock_t start,end;
    long double cpu_time_used;
    start = clock();
    long double sum = 0;

    struct Node* LinkedList = NULL;
    for(int i = 0 ; i < size; i ++){
        add_element(&LinkedList, i);
    }
    for(int i = 0; i < size; i++){
        sum = 0;
        for(int j = 0; j < 50; j++){
          start = clock();
        int tmp = get_value_at(&LinkedList, i);
        end = clock();  
        sum += ((long double) (end - start)) / CLOCKS_PER_SEC;
        }
        
        printf("Acces to %d element took: %.8Lf seconds on avarage\n",i,(long double)sum/50);
    }
    sum = 0;
    long double check = 0;
    for(int i = 0; i < size; i++){
        start = clock();
        r = rand()%size;
        check +=r;
        int tmp = get_value_at(&LinkedList,r);
        end = clock();
        sum += ((long double) ( end - start)) / CLOCKS_PER_SEC;
    }
    sum /= size;
    printf("Acces to random element took: %.10Lf seconds on avarage\n",sum);

    struct Node* MergeList1 = NULL;
    struct Node* MergeList2 = NULL;
    for(int i = 0; i< 3; i++){
        add_element(&MergeList1,i);
        add_element(&MergeList2,i);
    }
    merge(&MergeList1, &MergeList2);
    for(int i = 0; i< 6; i++){
        printf("element of merged list at %d is %d\n",i,get_value_at(&MergeList1, i));
    }
}