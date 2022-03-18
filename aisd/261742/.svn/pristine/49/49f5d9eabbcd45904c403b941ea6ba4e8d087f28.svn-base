#include <stdio.h>
#include <malloc.h>

struct Node
{
    struct Node *next;
    int value;
};

int pop(struct Node **queue){
    // printf("inside pop\n");
    if(*queue == NULL) {
        return -1;
    }
    else
    {
        struct Node* tmp = *queue;
        if(tmp->next == NULL){
            int tmp_val = tmp->value;
            *queue = NULL;
            free(*queue);
            return tmp_val;
        }
        while(tmp->next->next != NULL) tmp = tmp->next;
        int tmp_val = tmp->next->value;
        tmp->next = NULL;
        free(tmp->next);
        return tmp_val;
    }
    
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
        printf("%d\n", pop(&queue));
    }
    // push(&queue,1);
//     push(&queue,0);
//     push(&queue,1);
// // printf("%d\n", pop(&queue));
// printf("%d\n", pop(&queue));
// printf("%d\n", pop(&queue));

// push(&queue,3);
// printf("%d\n", pop(&queue));
}