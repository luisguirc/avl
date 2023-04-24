#ifndef AVL_H_
#define AVL_H_

#define max(a, b) (a > b ? a : b)

typedef struct node {
    int value, height;
    struct node* left;
    struct node* right;
} node;

node* create_node(int value);
node* insert(node* root, int value);
int height(node* root);
node* remove_node(node* root, int value);
void free_tree(node* root);

void print2D(node* root);

#endif