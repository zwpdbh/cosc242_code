

#include "bst.h"
#include <string.h>
#include "mylib.h"
struct bst_node {
    char *key;
    bst left;
    bst right;
};


bst bst_new() {
    bst b = NULL;
    
    return b;
}

bst bst_insert(bst b, char *str) {
    if (b == NULL) {
        b = emalloc(sizeof(bst));
        
        b->left = NULL;
        b->right = NULL;
        
        b->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(b->key, str);

        return b;
    }
    
    int keyInt = word_to_int(b->key);
    int insertInt = word_to_int(str);
    
    if (strcmp(b->key, str) == 0) {
        return b;
    }
    
    if (insertInt > keyInt) {
        b->right = bst_insert(b->right, str);
    } else {
        b->left = bst_insert(b->left, str);
    }

    return b;
}

int bst_search(bst b, char *str) {
    if (b == NULL) {
        return 0;
    }
    if (strcmp(str, b->key) == 0) {
        return 1;
    } else if (strcmp(str, b->key) < 0) {
        return bst_search(b->left, str);
    } else {
        return bst_search(b->right, str);
    }
}

void bst_inorder(bst b, void f(char *str)) {
    if (b == NULL) {
        return;
    }
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);
}

void bst_preorder(bst b, void f(char *str)) {
    if (b == NULL) {
        return;
    }
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

/**
 extern bst bst_delete(bst b, char *str);
 extern bst bst_free(bst b);
 */