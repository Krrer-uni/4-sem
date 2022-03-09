#include <stdio.h>


struct Node{
    int value;
    struct Node* next;
};
void add_element(struct Node** List, int value){
    struct Node* new = malloc(sizeof (struct Node));
    new->next = NULL;
    new->value = value;
    
    if(*List == NULL){
        return new;
    } else if((*List)->next ==NULL){
        (*List)->next = new;
    } else {
        struct Node* tmp = malloc(sizeof (struct Node));
        while (tmp->next->next != NULL) tmp = tmp->next;  
        tmp->next->next = new;
    }
}

int main(int argc, char* argv[]){

}