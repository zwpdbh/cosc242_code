#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

static tree_t tree_type;

struct tree_node {
    char *key;
    tree left;
    tree right;
    tree_colour colour;
    int frequency;
};


/**
 * helper function which rotate left on specified node r.
 * @param r is the node on which rotate tree left.
 * @return the tree after the operation.
 */
static tree left_rotate(tree r) {
    tree x = r->right;
    r->right = x->left;
    x->left = r;
    
    return x;
}

/**
 * helper function which rotate right on specified node r.
 * @param r is the node on which rotate tree right.
 * @return the tree after the operation.
 */
static tree right_rotate(tree r) {
    
    tree x = r->left;
    r->left = x->right;
    x->right = r;
    
    return x;
}

/**
 * a helper function which set the node and its both children's color.
 * @param r is the node on which we operate on.
 * @return r the tree after the operation.
 */
static tree flipColour(tree r) {
    r->colour = RED;
    r->left->colour = BLACK;
    r->right->colour = BLACK;
    return r;
}


/**
 * create a new tree base on the type.
 * @param type is the type you specified, could be:
 *  BST or RBT.
 * @param r the tree has been created.
 */
tree tree_new(tree_t type) {
    tree r = emalloc(sizeof(struct tree_node));
    r->key = NULL;
    r->left = NULL;
    r->right = NULL;
    tree_type = type;

    r->colour = RED;
    r->frequency = 0;
    
    return r;
}


/**
 * a helper method which fix RBT property based on node r
 * @param r the tree node to fix on.
 * @return the tree which has been fixed.
 */
static tree tree_fix(tree r) {
    if (IS_RED(r->left) && IS_RED(r->left->left) && IS_RED(r->right)) {
        r = flipColour(r);
    }
    if (IS_RED(r->left) && IS_RED(r->left->left) && IS_BLACK(r->right)) {
        r = right_rotate(r);
        r->colour = BLACK;
        r->right->colour = RED;
    }
    
    if (IS_RED(r->left) && IS_RED(r->left->right) && IS_RED(r->right)) {
        r = flipColour(r);
    }
    if (IS_RED(r->left) && IS_RED(r->left->right) && IS_BLACK(r->right)) {
        r->left = left_rotate(r->left);
        r = right_rotate(r);
        r->colour = BLACK;
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
    }
    
    if (IS_RED(r->right) && IS_RED(r->right->right) && IS_RED(r->left)) {
        r = flipColour(r);
    }
    
    if (IS_RED(r->right) && IS_RED(r->right->right) && IS_BLACK(r->left)) {
        r = left_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
    }
    
    return r;
}


/**
 * return a tree after inserting a key into the tree r
 * @param r the tree
 * @param str is the key
 * @return the tree
 */
tree tree_insert(tree r, char *str) {
    int cmp;
    if (r == NULL) {
        r = tree_new(tree_type);
    }
    
    if (r->key == NULL) {
        r->key = emalloc(sizeof(char) * (strlen(str) + 1));
        strcpy(r->key, str);
        r->frequency = 1;
        return r;
    }
    
    cmp = strcmp(str, r->key);
    if (cmp < 0) {
        r->left = tree_insert(r->left, str);
    } else if (cmp > 0) {
        r->right = tree_insert(r->right, str);
    } else if (cmp == 0) {
        r->frequency += 1;
    }
    
    if (tree_type == RBT) {
        r = tree_fix(r);
    }
    
    return r;
}

/**
 * search a key in a tree and return the searching result.
 * @param r the tree we are searching in.
 * @param str the key we are looking for in the tree.
 * @return int which 0 means search failed, otherwise return the key's freqs.
 */
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

/**
 * inorder traversal of tree.
 * @param r is the tree we want to traversal.
 * @param f is the passed in function for print out the key.
 */
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

/**
 * inorder traversal of tree.
 * @param r is the tree we want to traversal.
 * @param f is the passed in function for print out the key and its frequency.
 */
void tree_preorder(tree r, void f(int freq, char *str)) {
    if (r == NULL) {
        return;
    }
    if (r->key != NULL) {
        f(r->frequency, r->key);
    }
    if (r->left != NULL) {
        tree_preorder(r->left, f);
    }
    if (r->right != NULL) {
        tree_preorder(r->right, f);
    }
}


/**
 * free the memory a tree has been allocated.
 * @param r is the tree we want to free.
 * @param return the freed tree which is NULL.
 */
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

/**
 * set the root colour of a tree to black.
 * @param r is the tree we want to set.
 * @return return the modified tree.
 */
tree setColourBlack(tree r) {
    r->colour = BLACK;
    return r;
}

/**
 * return the depth of a tree.
 * @param r is the tree we want to get the depth.
 * @return a int which is the depth of the tree.
 */
int tree_depth(tree r) {
    int leftD;
    int rightD;
    
    if (r == NULL) {
        return 0;
    }
    
    if (r != NULL && r->left == NULL && r->right == NULL) {
        return 0;
    }
    
    if (r->left == NULL) {
        leftD = 0;
    } else {
        leftD = tree_depth(r->left);
    }
    
    if (r->right == NULL) {
        rightD = 0;
    } else {
        rightD = tree_depth(r->right);
    }
    
    if (rightD > leftD) {
        return 1 + rightD;
    } else {
        return 1 + leftD;
    }
}

/* These functions should be added to your tree.c file */

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
    if(t->key != NULL) {
        fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
                t->key, t->key, t->frequency,
                (RBT == tree_type && RED == t->colour) ? "red":"black");
    }
    if(t->left != NULL) {
        tree_output_dot_aux(t->left, out);
        fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
    }
    if(t->right != NULL) {
        tree_output_dot_aux(t->right, out);
        fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
    }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
    fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
    tree_output_dot_aux(t, out);
    fprintf(out, "}\n");
}



