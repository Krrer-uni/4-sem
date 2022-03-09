#include <stdio.h>
#include <stdlib.h>


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

int main(int argc, char* argv[]){
    struct Node* LinkedList = NULL;
    for(int i = 0 ; i < 1000; i ++){
        add_element(&LinkedList, i);
    }
    for(int i = 0; i < 1000; i++){
        printf("%d\n",get_value_at(&LinkedList, i));
    }
}