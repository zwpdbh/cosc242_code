
#ifndef rbt_h
#define rbt_h

#include <stdio.h>
typedef struct rbt_node *rbt;
typedef enum { RED, BLACK } rbt_colour;
typedef enum tree_e { BST, RBT } tree_t;


extern rbt rbt_free(rbt r);
extern void rbt_inorder(rbt r, void f(char *str));
extern rbt rbt_insert(rbt r, char *str);
extern rbt rbt_new(tree_t type);
extern void rbt_preorder(rbt r, void f(char *str));
extern int rbt_search(rbt r, char *key);

extern rbt setColourBlack(rbt);

#endif /* rbt_h */
