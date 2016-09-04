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


rbt left_rotate(rbt r) {
    
    rbt x = r->right;
    r->right = x->left;
    x->left = r;
    
    x->colour = r->colour;
    r->colour = RED;
    
    
    
    return x;
}

rbt right_rotate(rbt r) {
    
    rbt x = r->left;
    r->left = x->right;
    x->right = r;
    
    x->colour = r->colour;
    r->colour = RED;
    

    
    return x;
}

rbt flipColour(rbt r) {
    
    r->colour = RED;
    r->left->colour = BLACK;
    r->right->colour = BLACK;
    
    return r;
}

rbt rbt_new() {
    rbt r = NULL;
    return r;
}

rbt rbt_insert(rbt r, char *str) {
    int cmp;
    if (r == NULL) {
        r = emalloc(sizeof(struct rbt_node));
        r->colour = RED;
        r->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(r->key, str);
        r->left = NULL;
        r->right = NULL;
        return r;
    }
    
    cmp = strcmp(str, r->key);
    if (cmp < 0) {
        r->left = rbt_insert(r->left, str);
    } else if (cmp > 0) {
        r->right = rbt_insert(r->right, str);
    }
    
    if (IS_RED(r->right) && IS_BLACK(r->left)) {
        printf("Rotate Left on: %s\n", r->key);
        r = left_rotate(r);
    }
    if (IS_RED(r->left) && IS_RED(r->left->left)) {
        printf("Rotate Right on: %s\n", r->key);
        r = right_rotate(r);
    }
    if (IS_RED(r->left) && IS_RED(r->right)) {
        printf("Flip colour on: %s\n", r->key);
        r = flipColour(r);
    }
    
    return r;
}

int rbt_search(rbt r, char *str) {
    if (r == NULL) {
        return 0;
    }
    if (strcmp(str, r->key) == 0) {
        return 1;
    } else if (strcmp(str, r->key) < 0) {
        return rbt_search(r->left, str);
    } else {
        return rbt_search(r->right, str);
    }
}

void rbt_inorder(rbt r, void f(char *str)) {
    if (r == NULL) {
        return;
    }
    if (r->left != NULL) {
        rbt_inorder(r->left, f);
    }
    if (r->key != NULL) {
        f(r->key);
    }
    if (r->right != NULL) {
        rbt_inorder(r->right, f);
    }
}

void rbt_preorder(rbt r, void f(char *str)) {
    if (r == NULL) {
        return;
    }
    if (r->key != NULL) {
        if (IS_RED(r)) {
            printf("red:\t");
        } else if (IS_BLACK(r)) {
            printf("black:\t");
        }
        f(r->key);
    }
    if (r->left != NULL) {
        rbt_preorder(r->left, f);
    }
    if (r->right != NULL) {
        rbt_preorder(r->right, f);
    }
}

rbt rbt_delete(rbt r, char *str) {
    if (r == NULL) {
        return r;
    }
    if (strcmp(r->key, str) > 0) {
        r->left = rbt_delete(r->left, str);
        return r;
    } else if (strcmp(r->key, str) < 0) {
        r->right = rbt_delete(r->right, str);
        return r;
    } else {
        /**
         This is the case where find the key, and need to delete the node.
         */
        if (r->left == NULL && r->right == NULL) {
            free(r->key);
            free(r);
            r = NULL;
            return r;
        } else if (r->left == NULL && r->right != NULL) {
            free(r->key);
            free(r);
            r = r->right;
            return r;
        } else if (r->right == NULL && r->left != NULL) {
            free(r->key);
            free(r);
            r = r->left;
            return r;
        } else {
            rbt left_most;
            char word[256];
            rbt rightSubTree = r->right;
            while (rightSubTree->left != NULL) {
                rightSubTree = rightSubTree->left;
            }
            left_most = rightSubTree;
            
            strcpy(word, left_most->key);
            left_most->key = remalloc(left_most->key, strlen(r->key));
            strcpy(left_most->key, r->key);
            strcpy(r->key, word);
            
            r->right = rbt_delete(r->right, str);
            return r;
        }
    }
}



rbt rbt_free(rbt r) {
    if (r == NULL) {
        return NULL;
    } else if (r->key !=NULL && r->left == NULL && r->right == NULL) {
        free(r->key);
        r->key = NULL;
        free(r);
        r = NULL;
        return rbt_free(r);
    } else {
        r->left = rbt_free(r->left);
        r->right = rbt_free(r->right);
        return rbt_free(r);
    }
}

rbt setColourBlack(rbt r) {
    r->colour = BLACK;
    return r;
}
