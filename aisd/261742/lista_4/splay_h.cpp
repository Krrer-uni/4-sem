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
    node* nil;
    int size;
    char* left_trace;
    char* right_trace;

    int getHeight(struct node * n){
        SWAP++;
        if(n == nil) return 0;
        return 1+ max(getHeight(n->left), getHeight(n->right));
    }

    struct node* minimum(struct node* x){
        
        while(x->left != nil){
            SWAP+=2;
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
    if( root == nil ) return;
    if( root->left != nil ){
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
    if( root->right != nil ){
        right_trace[depth]='|';
        print_BST(root->right, depth+1, '\\');
    }
    }

    struct node* search(struct node * x, int k){
        SWAP++;
        COMP++;
        if(x == nil || x->val == k){
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

    void transplant(struct node*  u, struct node* v){
        SWAP++;
        if(u->parent == nil){
            SWAP++;
            root = v;
        } else if( u == u->parent->left){
            SWAP+=3;
            u->parent->left= v;
        } else{
            SWAP+=3;
            u->parent->right = v;
        }
        SWAP++;
        v->parent = u->parent;
    }

    void splay(struct node* x){
        while(x->parent != nil){
            SWAP++;
            SWAP++;
            if(x->parent->parent == nil){
                SWAP++;
                if(x->parent->left == x){
                    right_rotate(x->parent);    
                } else{
                    left_rotate(x->parent);
                }
            } else if(x == x->parent->left && x->parent == x->parent->parent->left){
                SWAP+=2;
                right_rotate(x->parent->parent);
                right_rotate(x->parent);
            } else if(x == x->parent->right && x->parent == x->parent->parent->right){
                SWAP+=4;
                left_rotate(x->parent->parent);
                left_rotate(x->parent);
            } else if(x == x->parent->right && x->parent == x->parent->parent->left){
                SWAP+=6;
                left_rotate(x->parent);
                right_rotate(x->parent);
            } else{
                right_rotate(x->parent);
                left_rotate(x->parent);
            }
        }
    }

    void deleteNode(struct node* z){
        SWAP++;
        struct node* y = z;
        struct node* x;
        SWAP++;
        if(z -> left == nil){
            SWAP++;
            x = z->right;
            transplant(z,z->right);
        } else if( z->right == nil){
            SWAP+2;
            x = z->left;
            transplant(z,z->left);
        } else{
            y = minimum(z->right);
            SWAP++;
            x = y->right;
            SWAP++;
            if(y->parent == z){
                SWAP++;
                x->parent = y;
            } else{
                transplant(y,y->right);
                SWAP+=2;
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z,y);
            SWAP++;
            SWAP++;
            y->left = z->left;
            y->left->parent = y;
        }
    }

    void left_rotate(struct node* x){
        SWAP++;
        auto y = x->right;
        SWAP++;
        x->right = y->left;
        SWAP++;
        if(y->left != nil){
            SWAP++;
            y->left->parent = x;
        }
        SWAP++;
        y->parent = x->parent;
        SWAP++;
        if(x->parent == nil){
            SWAP++;
            root = y;
        }else if(x == x->parent->left){
            SWAP+=3;
            x->parent->left = y;
        } else{
            SWAP+3;
            x->parent->right = y;
        }
        SWAP+=2;
        y->left = x;
        x->parent = y;
    }

    void right_rotate(struct node* x){
        SWAP++;
        SWAP++;
        auto y = x->left;
        x->left = y->right;
        SWAP++;
        if(y->right != nil){
            SWAP++;
            y->right->parent = x;
        }
        SWAP++;
        SWAP++;
        y->parent = x->parent;
        if(x->parent == nil){
            SWAP++;
            root = y;
        }else if(x == x->parent->right){
            SWAP++;
            SWAP++;
            x->parent->right = y;
        } else{
            SWAP++;SWAP++;
            x->parent->left = y;
        }
        SWAP++;SWAP++;
        y->right = x;
        x->parent = y;
    }

   

public:
    struct node* getroot(){
        return root;
    }

    int height(){
        return getHeight(root);
    }

    // void right_rotate(struct node* x){
    //     auto y = x->left;
    //     x->left = y->right;
    //     if(y->right != nil){
    //         y->right->parent = x;
    //     }
    //     y->parent = x->parent;
    //     if(x->parent == nil){
    //         root = y;
    //     }else if(x == x->parent->right){
    //         x->parent->right = y;
    //     } else{
    //         x->parent->left = y;
    //     }
    //     y->right = x;
    //     x->parent = y;
    // }

    void insert(int val){
        SWAP++;SWAP++;
        auto new_node = new node(val);
        new_node->left = nil;
        new_node->right = nil;
        new_node->parent = nil;
        if(root == nil){
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
                if(tmp->right == nil){
                    SWAP++;SWAP++;
                    tmp->right = new_node;
                    new_node->parent = tmp;
                    splay(new_node);
                    return;
                } else{
                    SWAP++;
                    tmp = tmp->right;
                    continue;
                }
            }else{
                SWAP++;
                if(tmp->left == nil){
                    SWAP++;SWAP++;
                    tmp->left = new_node;
                    new_node->parent = tmp;
                    splay(new_node);
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
        auto node = search(root,key);
        SWAP++;
        if(node == nil) return;
        deleteNode(node);
    }

    BST(int n){
        nil = new node(-1);
        root = nil;
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
        max_comp = max(max_comp, COMP - last_comp);
        cout << bst.height() << endl;
        if(n<50) {
        cout << "insert " << arr[i] << "\n";
        bst.print();
        }
    }
    random_shuffle(arr,arr+ n);

    for(int i = 0; i < n; i++){
        bst.deleteKey(arr[i]);
        cout << bst.height() << endl;
        if(n<50){
        cout << "delete " << arr[i] << "\n";
        bst.print();
        }
    }

    // cout << SWAP << " " << max_swap << " " << SWAP/n << " " << COMP <<  " " << max_comp << " " << COMP/n << endl;
}
