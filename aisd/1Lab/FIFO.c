#include <stdio.h>
#include <malloc.h>

struct Node
{
    struct Node *next;
    int value;
};

void pop(struct Node **queue){
    // printf("inside pop\n");
    if(*queue == NULL) {
        return;      
    }
    else
    {
        struct Node* tmp = *queue;
        *queue = (*queue)->next;
        free(tmp);
    }
    
}

int front(struct Node **queue){
    // printf("inside front\n");
    if(*queue == NULL) return -1;
    return (*queue)->value;
}

void push(struct Node **queue, int value){
    // printf("inside push\n");
    struct Node* new =  malloc(sizeof (struct Node));
    new->next = NULL;
    new->value = value;
    struct Node* tmp = *queue;
    if(tmp == NULL) {
        // printf("tmp == NULL\n");
        *queue = new;
        return;
    }
    else if(tmp->next==NULL){
        (*queue)->next = new;
        return;
    } 
    else while(tmp->next->next != NULL) {
        tmp = tmp->next;
        // printf("%d\n", tmp->next->value);
    }
    tmp->next->next = new;
    
}

int main(){
    struct Node *queue = NULL;
    for(int i = 0; i < 100; i++){
        push(&queue, i);
    }
    for(int i = 0; i < 100; i++){
        printf("%d\n", front(&queue));
        pop(&queue);
    }
}