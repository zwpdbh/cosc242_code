

#include "bst.h"
#include <string.h>
#include <stdlib.h>
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
        b = emalloc(sizeof(struct bst_node));
        b->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(b->key, str);
        b->left = NULL;
        b->right = NULL;
        return b;
    } else if (strcmp(b->key, str) == 0) {
        return b;
    } else if (strcmp(str, b->key) < 0) {
        b->left = bst_insert(b->left, str);
        return b;
    } else {
        b->right = bst_insert(b->right, str);
        return b;
    }
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

bst bst_delete(bst b, char *str) {
    if (b == NULL) {
        return b;
    }
    if (strcmp(b->key, str) > 0) {
        return bst_delete(b->left, str);
    } else if (strcmp(b->key, str) < 0) {
        return bst_delete(b->right, str);
    } else {
        /**
         This is the case where find the key, and need to delete the node.
         */
        if (b->left == NULL && b->right == NULL) {
            free(b->key);
            b->key = NULL;
            free(b);
            b = NULL;
            return b;
        } else if (b->left == NULL && b->right != NULL) {
            bst tmp = b;
            b = b->right;
            free(tmp->key);
            free(tmp->right);
            tmp->right = NULL;
            return b;
        } else if (b->right == NULL && b->left != NULL) {
            bst tmp = b;
            b = b->left;
            free(tmp->key);
            free(tmp->left);
            tmp->left = NULL;
            return b;
        } else {
            bst left_most;
            bst left = b->right;
            while (left != NULL) {
                left = left->left;
            }
            left_most = left;
            swap(left_most->key, b->key);
            return bst_delete(b->right, str);
        }
    }
}



bst bst_free(bst b) {
    free(b->key);
    b->key = NULL;
    free(b->left);
    b->left = NULL;
    free(b->right);
    b->right = NULL;
    free(b);
    b = NULL;
    return NULL;
}
