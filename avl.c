#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

#define COUNT 10

node* create_node(int value){
    node* root = (node*) malloc(sizeof(node));
    root->value = value;
    root->height = 0;
    root->left = root->right = NULL;
    return root;
}

int height(node* root){
    if(root == NULL) return -1;
    return root->height;
}

void update_height(node* root){
    root->height = max(height(root->left), height(root->right)) + 1;
}

int get_balance(node* root){
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

node* left_left(node* root){
    node* pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;

    update_height(root);
    update_height(pivot);
    return pivot;
}

node* right_right(node* root){
    node* pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;

    update_height(root);
    update_height(pivot);
    return pivot;
}

node* left_right(node* root){
    root->left = right_right(root->left);
    return left_left(root);
}

node* right_left(node* root){
    root->right =left_left(root->right);
    return right_right(root);
}

node* rebalance(node* root){
    if(root == NULL) return root;

    if(get_balance(root) > 1){
        if(get_balance(root->left) >= 0) root = left_left(root);
        else root = left_right(root);
    } else if (get_balance(root) < -1){
        if(get_balance(root->right) <= 0) root = right_right(root);
        else root = right_left(root);
    }

    return root;
}

node* insert(node* root, int value){
    if(root == NULL){
        return create_node(value);
    }

    if(value < root->value){
        root->left = insert(root->left, value);
        update_height(root);
        if(get_balance(root) > 1){
            if(value < root->left->value) root = left_left(root);
            else root = left_right(root);
        }
    } else if (value > root->value){
        root->right = insert(root->right, value);
        update_height(root);
        if(get_balance(root) < -1){
            if(value > root->right->value) root = right_right(root);
            else root = right_left(root);
        }
    }

    update_height(root);
    return root;
}

node* smallest_node(node* root) {
    node* walker = root;
    while( walker->left != NULL) walker = walker->left;
    return walker;
}

node* remove_node(node* root, int value) {
    node* t;
    if (root == NULL) {
        return NULL;
    }
    if (value == root->value) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->right == NULL) {
            t = root->left;
            free(root);
            return rebalance(t);
        } else if (root->left == NULL) {
            t = root->right;
            free(root);
            return rebalance(t);
        } else {
            t = smallest_node(root->right);
            root->value = t->value;
            root->right = remove_node(root->right, t->value);
            return rebalance(root);
        }
    } else if (value < root->value) {
        root->left = remove_node(root->left, value);
    } else {
        root->right = remove_node(root->right, value);
    }

    return rebalance(root);
}

void free_tree(node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print2DUtil(node* root, int space)
{
    // Base case
    if (root == NULL){
        return;
    }
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}