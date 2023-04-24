#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

void operation(char option, node** root){
    int value;
    switch (option)
    {
        case 'I': ;
            scanf("%d", &value);
            *root = insert(*root, value);
            break;
        
        case 'P':
            print2D(*root);
            break;
        
        case 'R': ;
            scanf("%d", &value);
            *root = remove_node(*root, value);
            break;

        case 'F': ;
        free_tree(*root);

        default:
            break;
    }
}

int main(int argc, char const *argv[])
{
    char option;
    node* root = NULL;

    do{
        scanf(" %c", &option);
        operation(option, &root);
    } while (option != 'F');

    return 0;
}

// melhoria: usar valgrind para detectar memory leak.