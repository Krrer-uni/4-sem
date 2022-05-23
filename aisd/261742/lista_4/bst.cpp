#include <iostream>
#include <algorithm>
using namespace std;
int SWAP = 0;
int COMP = 0;


class BST {

    struct node{
    int val;
    node* left;
    node* right;
    node* parent;

    node(int x) : val(x), left(NULL), right(NULL), parent(NULL){}

    };

    node* root;
    int size;
    char* left_trace;
    char* right_trace;

    int getHeight(struct node * n){
        SWAP++;
        if(n == NULL) return 0;
        return 1+ max(getHeight(n->left), getHeight(n->right));
    }

    struct node* minimum(struct node* x){
        while(x->left != NULL){
            SWAP++;
            x = x->left;
        }
        return x;
    }

    // struct node* succesor(struct node* x){
    //     if(x->right != NULL){
    //         return minimum(x->right);
    //     }
    //     auto y = x->parent;
    //     while( y != NULL && x == y->right){
    //         x = y;
    //         y = y->parent;
    //     }
    // }

    void print_BST( struct node * root, int depth,char prefix){
    if( root == NULL ) return;
    if( root->left != NULL ){
        print_BST(root->left, depth+1, '/');
    }
    if(prefix == '/') left_trace[depth-1]='|';
    if(prefix == '\\') right_trace[depth-1]=' ';
    if( depth==0) printf("-");
    if( depth>0) printf(" ");
    for(int i=0; i<depth-1; i++)
        if( left_trace[i]== '|' || right_trace[i]=='|' ) {
        printf("| ");
        } else {
        printf("  ");
        }
    if( depth>0 ) printf("%c-", prefix);
    printf("%d\n", root->val);
    left_trace[depth]=' ';
    if( root->right != NULL ){
        right_trace[depth]='|';
        print_BST(root->right, depth+1, '\\');
    }
    }

    struct node* search(struct node * x, int k){
        SWAP++;
        COMP++;
        if(x == NULL || x->val == k){
            return x;
        }
        COMP++;
        if(k < x->val){
            return search(x->left, k);
        }
        else{
            return search(x->right,k);
        }
    }

    void deleteNode(struct node* node){
        SWAP+=2;
        if(node->left == NULL && node->right == NULL){
            SWAP++;
            if(node->parent != NULL){
                SWAP+=2;
                if(node->parent->left == node) node->parent->left = NULL;
                else node->parent->right = NULL;
            } else{
                SWAP++;
                root = NULL;
            }
            free(node);
        } else if(node->right == NULL){
            SWAP+=2;
            node->left->parent = node->parent;
            SWAP++;
            if(node->parent != NULL){
                SWAP+=2;
                if(node->parent->left == node) node->parent->left = node->left;
                else node->parent->right = node->left;
            } else{
                root = node->left;
            }
            free(node);
            
        } else if(node->left == NULL){
            SWAP+=2;
            node->right->parent = node->parent;
            SWAP++;
            if(node->parent != NULL){
                SWAP+2;
                if(node->parent->left == node) node->parent->left = node->right;
                else node->parent->right = node->right;
            } else{
                SWAP++;
                root = node->right;
            }
            free(node);
        } else{
            SWAP+=4;
            auto tmp = minimum(node->right);
            COMP++;
            node->val = tmp->val;
            deleteNode(tmp);
        }
    }



public:
    int height(){
        return getHeight(root);
    }

    void insert(int val){
        SWAP++;
        COMP++;
        auto new_node = new node(val);
        SWAP++;
        if(root == NULL){
            SWAP++;
            root = new_node;
            return;
        }
        SWAP++;
        auto tmp = root;
        while(true){
            COMP++;
            if(val > tmp->val){
                SWAP++;
                if(tmp->right == NULL){
                    SWAP+=2;
                    tmp->right = new_node;
                    new_node->parent = tmp;
                    return;
                } else{
                    SWAP++;
                    tmp = tmp->right;
                    continue;
                }
            }else{
                SWAP++;
                if(tmp->left == NULL){
                    SWAP+=2;
                    tmp->left = new_node;
                    new_node->parent = tmp;
                    return;
                } else{
                    SWAP++;
                    tmp = tmp->left;
                    continue;
                }
            }
        }
    }

    void print(){
        print_BST(root,0,'-');

    }

    void deleteKey(int key){
        SWAP+=2;
        auto node = search(root,key);
        if(node == NULL) return;
        deleteNode(node);
    }

    BST(int n){
        root = NULL;
        size = n;
        left_trace= (char*)malloc( size*sizeof(char) );
        right_trace= (char*)malloc( size*sizeof(char) );
        for(int i=0; i<=size; i++){
        left_trace[i]=' ';
        left_trace[i]=' ';
        }
    }

};


int main(int argc, char* argv[]){
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(n<50) cout << arr[i] << " ";
    }
    if(n<50) cout << "\n";

    BST bst(n);
    int max_swap = 0;
    int max_comp = 0;
    for(int i = 0; i < n; i++){
        int last_swap = SWAP;
        int last_comp = COMP;
        bst.insert(arr[i]);
        max_swap = max(max_swap, SWAP - last_swap);
        max_comp = max(max_comp,COMP - last_comp);
        if(n<50) {
        cout << "insert " << arr[i] << "\n";
        bst.print();
        }
    }
    random_shuffle(arr,arr+ n);

    for(int i = 0; i < n; i++){
        bst.deleteKey(arr[i]);
        if(n<50){
        cout << "delete " << arr[i] << "\n";
        bst.print();
        }
    }

    cout << SWAP << " " << max_swap << " " << SWAP/n << " " << COMP <<  " " << max_comp << " " << COMP/n << endl;
}
