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

extern rbt rbt_delete(rbt b, char *str);
extern rbt rbt_free(rbt b);
extern void rbt_inorder(rbt b, void f(char *str));
extern rbt rbt_insert(rbt b, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt b, void f(char *str));
extern int rbt_search(rbt b, char *key);

#endif /* rbt_h */