#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/**
 * Static varible for storing the type of tree, which is a enum
 * either BST OR RBT.
 */
static tree_t tree_type;


/**
 * SOmething here.......................................
 *
 */
struct tree_node {
    char *key;
    tree left;
    tree right;
    tree_colour colour;
    int frequency;
};

/**
 * A helper function which peforms a left-rotation of the given tree.
 *
 * @param r is the node that will be rotated.
 * @return the the new rotated state tree.
 */
static tree left_rotate(tree r) {
    tree x = r->right;
    r->right = x->left;
    x->left = r;
    
    return x;
}

/**
 * A helper function which performs a right-rotation of the given tree.
 *
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
 * A helper function which sets the colour of a tree's root node
 * and both of its children.
 * 
 * @param r is the tree on which we operate on.
 * @return r after the colours have been set.
 */
static tree flipColour(tree r) {
    r->colour = RED;
    r->left->colour = BLACK;
    r->right->colour = BLACK;
    return r;
}

/**
 * Creates a new empty tree of the type given.
 *
 * @param type the type of tree to be created (BST or RBT).
 * @return r the new tree.
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
 * A helper method which is used to fix an RBT tree to maintain its RED BLACK
 * ordering property.
 * 
 * @param r the RBT to fix.
 * @return the fixed tree. 
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
 * This function inserts a given key into a tree if it does not exist,
 * otherwise increments the frequency.
 *
 * If the tree_type is an RBT then the tree_fix will be called on
 * the tree before it is returned. 
 *
 * @param r the tree to be inserted into.
 * @param str is the key to be inserted.
 * @return the tree after insertion
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
 * Search a tree for a given key and return if it is found.
 *
 * @param r the tree we are searching in.
 * @param str the key we are looking for in the tree.
 * @return 1 if key found else 0 if search failed. 
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
 * Traverses a tree using a preorder traversal, sending visited nodes to
 * the given parameter function to be printed out.
 *
 * @param r is the tree we want to traverse.
 * @param f a function for printting out the node's key and frequency.
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
 * Free the memory that has been allocated to a tree.
 *
 * @param r is the tree we want to free.
 * @preturn NULL once the tree has been freed.
 */
tree tree_free(tree r) {
    free(r->key);
    if (r->left != NULL) {
        r->left = tree_free(r->left);
    }
    if (r->right != NULL) {
        r->right = tree_free(r->right);
    }
    free(r);
    return NULL;
}

/**
 * Sets the root colour of a tree to black.
 *
 * @param r is the tree we want to set.
 * @return return the modified tree.
 */
tree setColourBlack(tree r) {
    r->colour = BLACK;
    return r;
}

/**
 * Traverses a tree to calculate and return its depth.
 *
 * @param r is the tree we want traverse.
 * @return the depth of the tree.
 *//*
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
    }*/


int tree_depth(tree t) {
    if (t == NULL) {
        return 0;
    }else {
        int leftB = 0, rightB = 0;
        if (t->left != NULL) {
            leftB += 1 + tree_depth(t->left);
        }
        if (t->right != NULL) {
            rightB += 1 + tree_depth(t->right);
        }
        return (leftB >= rightB ? leftB : rightB);
    }
    }

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
