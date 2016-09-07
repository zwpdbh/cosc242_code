
#ifndef tree_h
#define tree_h

#include <stdio.h>
typedef struct tree_node *tree;
typedef enum { RED, BLACK } tree_colour;
typedef enum tree_e { BST, RBT } tree_t;


extern tree tree_free(tree r);
extern void tree_inorder(tree r, void f(char *str));
extern tree tree_insert(tree r, char *str);
extern tree tree_new(tree_t type);
extern void tree_preorder(tree r, void f(char *str));
extern int tree_search(tree r, char *key);

extern tree setColourBlack(tree);

#endif /* tree_h */