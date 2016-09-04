//
//  rbt.h
//  lab16_RBT
//
//  Created by zwpdbh on 9/3/16.
//  Copyright © 2016 Otago. All rights reserved.
//


#ifndef rbt_h
#define rbt_h

#include <stdio.h>
typedef struct rbt_node *rbt;
typedef enum { RED, BLACK } rbt_colour;

extern rbt rbt_delete(rbt r, char *str);
extern rbt rbt_free(rbt r);
extern void rbt_inorder(rbt r, void f(char *str));
extern rbt rbt_insert(rbt r, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt r, void f(char *str));
extern int rbt_search(rbt r, char *key);
extern rbt right_rotate(rbt r);
extern rbt left_rotate(rbt r);
extern rbt flipColour(rbt r);

#endif /* rbt_h */