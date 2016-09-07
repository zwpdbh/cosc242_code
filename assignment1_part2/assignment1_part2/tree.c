#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

struct tree_node {
    char *key;
    tree left;
    tree right;
    tree_colour colour;
    tree_t tree_type;
};


static tree left_rotate(tree r) {
    
    tree x = r->right;
    r->right = x->left;
    x->left = r;
    
    return x;
}

static tree right_rotate(tree r) {
    
    tree x = r->left;
    r->left = x->right;
    x->right = r;
    
    return x;
}

static tree flipColour(tree r) {
    r->colour = RED;
    r->left->colour = BLACK;
    r->right->colour = BLACK;
    return r;
}

tree tree_new(tree_t type) {
    tree r = emalloc(sizeof(struct tree_node));
    r->key = NULL;
    r->left = NULL;
    r->right = NULL;
    r->tree_type = type;
    r->colour = RED;
    
    return r;
}

static tree tree_fix(tree r) {
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

tree tree_insert(tree r, char *str) {
    int cmp;
    if (r == NULL) {
        r = tree_new(r->tree_type);
    }
    
    if (r->key == NULL) {
        r->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(r->key, str);
        return r;
    }
    
    cmp = strcmp(str, r->key);
    if (cmp < 0) {
        r->left = tree_insert(r->left, str);
    } else if (cmp > 0) {
        r->right = tree_insert(r->right, str);
    }
    
    if (r->tree_type == RBT) {
        r = tree_fix(r);
    }
    
    return r;
}

int tree_search(tree r, char *str) {
    if (r == NULL) {
        return 0;
    }
    if (strcmp(str, r->key) == 0) {
        return 1;
    } else if (strcmp(str, r->key) < 0) {
        return tree_search(r->left, str);
    } else {
        return tree_search(r->right, str);
    }
}

void tree_inorder(tree r, void f(char *str)) {
    if (r == NULL) {
        return;
    }
    if (r->left != NULL) {
        tree_inorder(r->left, f);
    }
    if (r->key != NULL) {
        f(r->key);
    }
    if (r->right != NULL) {
        tree_inorder(r->right, f);
    }
}

void tree_preorder(tree r, void f(char *str)) {
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
        tree_preorder(r->left, f);
    }
    if (r->right != NULL) {
        tree_preorder(r->right, f);
    }
}



tree tree_free(tree r) {
    
    if (r->key != NULL) {
        free(r->key);
        r->key = NULL;
    }
    if (r->left != NULL) {
        r->left = tree_free(r->left);
    }
    if (r->right != NULL) {
        r->right = tree_free(r->right);
    }
    
    if (r->key == NULL && r->left == NULL && r->right == NULL) {
        free(r);
        r = NULL;
    }
    
    return NULL;
}

tree setColourBlack(tree r) {
    r->colour = BLACK;
    return r;
}
