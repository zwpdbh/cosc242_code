//
//  rbt.c
//  lab16_RBT
//
//  Created by zwpdbh on 9/3/16.
//  Copyright © 2016 Otago. All rights reserved.
//



#include "rbt.h"
#include <string.h>
#include <stdlib.h>
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

struct rbt_node {
    char *key;
    rbt left;
    rbt right;
    rbt_colour colour;
};


rbt rbt_new() {
    rbt b = NULL;
    return b;
}

rbt rbt_insert(rbt b, char *str) {
    if (b == NULL) {
        b = emalloc(sizeof(struct rbt_node));
        b->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(b->key, str);
        b->left = NULL;
        b->right = NULL;
        return b;
    } else if (strcmp(b->key, str) == 0) {
        return b;
    } else if (strcmp(str, b->key) < 0) {
        b->left = rbt_insert(b->left, str);
        return b;
    } else {
        b->right = rbt_insert(b->right, str);
        return b;
    }
}

int rbt_search(rbt b, char *str) {
    if (b == NULL) {
        return 0;
    }
    if (strcmp(str, b->key) == 0) {
        return 1;
    } else if (strcmp(str, b->key) < 0) {
        return rbt_search(b->left, str);
    } else {
        return rbt_search(b->right, str);
    }
}

void rbt_inorder(rbt b, void f(char *str)) {
    if (b == NULL) {
        return;
    }
    if (b->left != NULL) {
        rbt_inorder(b->left, f);
    }
    if (b->key != NULL) {
        f(b->key);
    }
    if (b->right != NULL) {
        rbt_inorder(b->right, f);
    }
}

void rbt_preorder(rbt b, void f(char *str)) {
    if (b == NULL) {
        return;
    }
    if (b->key != NULL) {
        f(b->key);
    }
    if (b->left != NULL) {
        rbt_preorder(b->left, f);
    }
    if (b->right != NULL) {
        rbt_preorder(b->right, f);
    }
}

rbt rbt_delete(rbt b, char *str) {
    if (b == NULL) {
        return b;
    }
    if (strcmp(b->key, str) > 0) {
        b->left = rbt_delete(b->left, str);
        return b;
    } else if (strcmp(b->key, str) < 0) {
        b->right = rbt_delete(b->right, str);
        return b;
    } else {
        /**
         This is the case where find the key, and need to delete the node.
         */
        if (b->left == NULL && b->right == NULL) {
            free(b->key);
            free(b);
            b = NULL;
            return b;
        } else if (b->left == NULL && b->right != NULL) {
            free(b->key);
            free(b);
            b = b->right;
            return b;
        } else if (b->right == NULL && b->left != NULL) {
            free(b->key);
            free(b);
            b = b->left;
            return b;
        } else {
            rbt left_most;
            char word[256];
            rbt rightSubTree = b->right;
            while (rightSubTree->left != NULL) {
                rightSubTree = rightSubTree->left;
            }
            left_most = rightSubTree;
            
            strcpy(word, left_most->key);
            left_most->key = remalloc(left_most->key, strlen(b->key));
            strcpy(left_most->key, b->key);
            strcpy(b->key, word);
            
            b->right = rbt_delete(b->right, str);
            return b;
        }
    }
}



rbt rbt_free(rbt b) {
    if (b == NULL) {
        return NULL;
    } else if (b->key !=NULL && b->left == NULL && b->right == NULL) {
        free(b->key);
        b->key = NULL;
        free(b);
        b = NULL;
        return rbt_free(b);
    } else {
        b->left = rbt_free(b->left);
        b->right = rbt_free(b->right);
        return rbt_free(b);
    }
}
