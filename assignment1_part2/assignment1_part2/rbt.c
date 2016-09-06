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
    tree_t tree_type;
};


static rbt left_rotate(rbt r) {
    
    rbt x = r->right;
    r->right = x->left;
    x->left = r;
    
    return x;
}

static rbt right_rotate(rbt r) {
    
    rbt x = r->left;
    r->left = x->right;
    x->right = r;

    return x;
}

static rbt flipColour(rbt r) {
    r->colour = RED;
    r->left->colour = BLACK;
    r->right->colour = BLACK;
    return r;
}

rbt rbt_new(tree_t type) {
    rbt r = emalloc(sizeof(struct rbt_node));
    r->key = NULL;
    r->left = NULL;
    r->right = NULL;
    r->tree_type = type;
    r->colour = RED;
    
    return r;
}

static rbt rbt_fix(rbt r) {
    if (IS_RED(r->left) && IS_RED(r->left->left) && IS_RED(r->right)) {
        r = flipColour(r);
    }
    if (IS_RED(r->left) && IS_RED(r->left->left) && IS_BLACK(r->right)) {
        r = right_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
        r->right->colour = RED;
    }
    
    if (IS_RED(r->left) && IS_RED(r->left->right) && IS_RED(r->right)) {
        r = flipColour(r);
    }
    if (IS_RED(r->left) && IS_RED(r->left->right) && IS_BLACK(r->right)) {
        r->left = left_rotate(r->left);
        r = right_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
        r->right->colour = RED;
    }
    
    if (IS_RED(r->right) && IS_RED(r->right->left) && IS_RED(r->left)) {
        r = flipColour(r);
    }
    if (IS_RED(r->right) && IS_RED(r->right->left) && IS_BLACK(r->left)) {
        r->right = right_rotate(r->right);
        r = left_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
        r->right->colour = RED;
    }
    
    if (IS_RED(r->right) && IS_RED(r->right->right) && IS_RED(r->left)) {
        r = flipColour(r);
    }
    
    if (IS_RED(r->right) && IS_RED(r->right->right) && IS_BLACK(r->left)) {
        r = left_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
        r->right->colour = RED;
    }
    
    return r;
}

rbt rbt_insert(rbt r, char *str) {
    int cmp;
    if (r == NULL) {
        r = rbt_new(RBT);
    }
    
    if (r->key == NULL) {
        r->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(r->key, str);
        return r;
    }
    
    cmp = strcmp(str, r->key);
    if (cmp < 0) {
        r->left = rbt_insert(r->left, str);
    } else if (cmp > 0) {
        r->right = rbt_insert(r->right, str);
    }
    
    if (r->tree_type == RBT) {
        r = rbt_fix(r);
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



rbt rbt_free(rbt r) {

    if (r->key != NULL) {
        free(r->key);
        r->key = NULL;
    }
    if (r->left != NULL) {
        r->left = rbt_free(r->left);
    }
    if (r->right != NULL) {
        r->right = rbt_free(r->right);
    }
    
    if (r->key == NULL && r->left == NULL && r->right == NULL) {
        free(r);
        r = NULL;
    }
    
    return NULL;
}

rbt setColourBlack(rbt r) {
    r->colour = BLACK;
    return r;
}
