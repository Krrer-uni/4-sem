#include <iostream>
#include <algorithm>
using namespace std;
int abc = 0;
int SWAP = 0;


class BST {
    enum Color{red,black};

    struct node{
    int val;
    node* left;
    node* right;
    node* parent;
    Color c;

    node(int x) : val(x), left(NULL), right(NULL), parent(NULL), c(red){}

    };

    node* root;
    node* nil;
    int size;
    char* left_trace;
    char* right_trace;

    int getHeight(struct node * n){
        abc++;
        if(n == nil) return 0;
        return 1+ max(getHeight(n->left), getHeight(n->right));
    }

    struct node* minimum(struct node* x){
        
        while(x->left != nil){
            abc++;
            abc++;
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
        abc++;
        SWAP++;
        if(x == nil || x->val == k){
            return x;
        }
        SWAP++;
        if(k < x->val){
            return search(x->left, k);
        }
        else{
            return search(x->right,k);
        }
    }

    void transplant(struct node*  u, struct node* v){
        if(u->parent == nil){
            abc+=2;
            root = v;
        } else if( u == u->parent->left){
            abc+=3;
            u->parent->left= v;
        } else{
            abc+=3;
            u->parent->right = v;
        }
        abc++;
        v->parent = u->parent;
    }

    void deleteFix(struct node* x){
        while (x != root && x->c == black){
            abc++;
            if(x == x->parent->left){
                abc++;
                abc++;
                struct node* w = x->parent->right;
                if(w->c == red){
                    w->c = black;
                    x->parent->c = red;
                    left_rotate(x->parent);
                    abc++;
                    w = x->parent->right;
                }
                if(w->left->c == black && w->right->c == black){
                    w->c = red;
                    abc++;
                    x = x->parent;
                }
                else{
                    if( w->right->c == black){
                        w->left->c = black;
                        w->c = red;
                        right_rotate(w);
                        abc++;
                        w = x->parent->right;
                    }
                    w->c = x->parent->c;
                    x->parent->c = black;
                    w->right->c = black;
                    left_rotate(x->parent);
                    abc++;
                    x = root;
                } 
            } else{
                abc++;
                 struct node* w = x->parent->left;
                if(w->c == red){
                    w->c = black;
                    x->parent->c = red;
                    right_rotate(x->parent);
                    abc++;
                    w = x->parent->left;
                }
                if(w->right->c == black && w->left->c == black){
                    w->c = red;
                    abc++;
                    x = x->parent;
                }
                else{
                    if( w->left->c == black){
                        w->right->c = black;
                        w->c = red;
                        left_rotate(w);
                        abc++;
                        w = x->parent->left;
                    }
                    w->c = x->parent->c;
                    x->parent->c = black;
                    w->left->c = black;
                    right_rotate(x->parent);
                    abc++;
                    x = root;
                } 
            }
        }
        x->c = black;
    }

    void deleteNode(struct node* z){
        struct node* y = z;
        Color y_col = y->c;
        struct node* x;
        if(z -> left == nil){
            abc+=2;
            x = z->right;
            transplant(z,z->right);
        } else if( z->right == nil){
            abc+=3;
            x = z->left;
            transplant(z,z->left);
        } else{
            abc+=2;
            y = minimum(z->right);
            y_col = y->c;
            abc++;
            x = y->right;
            abc++;
            if(y->parent == z){
                abc++;
                x->parent = y;
            } else{
                transplant(y,y->right);
                abc+=2;
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z,y);
            abc+=2;
            y->left = z->left;
            y->left->parent = y;
            y->c = z->c;
        }
        if(y_col == black){
            deleteFix(x);
        }
    }

    void left_rotate(struct node* x){
        abc++;
        auto y = x->right;
        abc++;
        x->right = y->left;
        abc++;
        if(y->left != nil){
            abc++;
            y->left->parent = x;
        }
        abc++;
        y->parent = x->parent;
        abc++;
        if(x->parent == nil){
            abc++;
            root = y;
        }else if(x == x->parent->left){
            abc+=3;
            x->parent->left = y;
        } else{
            abc+=3;
            x->parent->right = y;
        }
        abc+=2;
        y->left = x;
        x->parent = y;
    }

    void right_rotate(struct node* x){
        abc++;
        auto y = x->left;
        abc++;
        x->left = y->right;
        abc++;
        if(y->right != nil){
            abc++;
            y->right->parent = x;
        }
        abc++;
        y->parent = x->parent;
        abc++;
        if(x->parent == nil){
            abc++;
            root = y;
        }else if(x == x->parent->right){
            abc+=3;
            x->parent->right = y;
        } else{
            abc+=3;
            x->parent->left = y;
        }
        abc+=2;
        y->right = x;
        x->parent = y;
    }

    void insert_fix(struct node* z){
        while(z->parent->c == red){
            abc++;
            if(z->parent == z->parent->parent->left){
                abc++;
                struct node * y = z->parent->parent->right;
                if(y->c == red){
                    z->parent->c = black;
                    y->c = black;
                    z->parent->parent->c = red;
                    abc++;
                    z = z->parent->parent;
                } else {
                    abc++;
                    if(z == z->parent->right){
                        abc++;
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->c = black;
                    z->parent->parent->c = red;
                    right_rotate(z->parent->parent);
                }
            } else{
                abc++;
                 struct node * y = z->parent->parent->left;
                if(y->c == red){
                    z->parent->c = black;
                    y->c = black;
                    z->parent->parent->c = red;
                    abc++;
                    z = z->parent->parent;
                } else {
                    abc++;
                    if(z == z->parent->left){
                        abc++;
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->c = black;
                    z->parent->parent->c = red;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->c = black;
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
        abc+=2;
        auto new_node = new node(val);
        new_node->left = nil;
        new_node->right = nil;
        new_node->parent = nil;
        if(root == nil){
            abc++;
            root = new_node;
            insert_fix(new_node);
            return;
        }
        abc++;
        auto tmp = root;
        while(true){
            SWAP++;
            if(val > tmp->val){
                abc++;
                if(tmp->right == nil){
                    abc+=2;
                    tmp->right = new_node;
                    new_node->parent = tmp;
                    insert_fix(new_node);
                    return;
                } else{
                    abc++;
                    tmp = tmp->right;
                    continue;
                }
            }else{
                abc++;
                if(tmp->left == nil){
                    abc+=2;
                    tmp->left = new_node;
                    new_node->parent = tmp;
                    insert_fix(new_node);
                    return;
                } else{
                    abc++;
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
        abc++;
        if(node == nil) return;
        deleteNode(node);
    }

    BST(int n){
        nil = new node(-1);
        nil->c = black;
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
        int last_swap = abc;
        int last_comp = SWAP;
        bst.insert(arr[i]);
        max_swap = max(max_swap, abc - last_swap);
        max_comp = max(max_comp,SWAP - last_comp);
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

    cout << abc << " " << max_swap << " " << abc/n << " " << SWAP <<  " " << max_comp << " " << SWAP/n << endl;
}
