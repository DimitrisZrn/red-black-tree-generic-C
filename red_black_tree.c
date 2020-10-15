/*********************************************************************
 * Author: Zournatzis Dimitrios
 * Generic data type Red Black Tree implementation in C
 * Based on textbook: "Introduction to Algorithms - Cormen, Leiserson, 
 * 													Rivest, Stein
 *
 * file: red_black_tree.c
 *********************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "red_black_tree.h"

rbt_tree *rbt_init(cmpr_f cmpfunc){
	rbt_tree *t = malloc(sizeof(rbt_tree));
	rbt_node *nil = malloc(sizeof(rbt_node));
	nil->right = NULL;
	nil->left = NULL;
	nil->up = NULL;
	nil->data = NULL;
	nil->color = BLACK;
	t->nil = nil;
	t->root = t->nil;
	t->cmpfunc = cmpfunc;
	return t;
}

rbt_node *rbt_newNode(void* data, size_t data_size){
	rbt_node* new = malloc(sizeof(rbt_node));
	new->data = malloc(data_size);
	memcpy(new->data, data, data_size);
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	new->color = BLACK;
	return new;
}

void rbt_leftRotate(rbt_tree* t, rbt_node* x){
	rbt_node* y = x->right;
	x->right = y->left;

	if(y->left != t->nil)
		y->left->up = x;

	y->up = x->up;
	if(x->up == t->nil)
		t->root = y;
	else if(x == x->up->left)
		x->up->left = y;
	else
		x->up->right = y;

	y->left = x;
	x->up= y;
}

void rbt_rightRotate(rbt_tree* t, rbt_node* x){
	rbt_node* y = x->left;
	x->left = y->right;

	if(y->right != t->nil)
		y->right->up = x;

	y->up = x->up;

	if(x->up == t->nil)
		t->root = y;
	else if(x == x->up->right)
		x->up->right = y;
	else
		x->up->left = y;

	y->right = x;
	x->up= y;
}

void rbt_insertFix(rbt_tree* t, rbt_node* z){
	rbt_node* y;

	while(z->up->color == RED){
		if(z->up == z->up->up->left){
			y = z->up->up->right;

			if(y->color == RED){
				z->up->color = BLACK;
				z->color = BLACK;
				z->up->up->color = RED;
				z = z->up->up;
			}else{
				if(z == z->up->right){
					z = z->up;
					rbt_leftRotate(t, z);
				} 

				z->up->color = BLACK;
				z->up->up->color = RED;
				rbt_rightRotate(t, z->up->up);
			} 

		} 
		else{

			y = z->up->up->left;

			if(y->color == RED){
				z->up->color = BLACK;
				y->color = BLACK;
				z->up->up->color = BLACK;
				z = z->up->up;
			}else{
				if(z == z->up->left){
					z = z->up;
					rbt_rightRotate(t, z);
				} 

				z->up->color = BLACK;
				z->up->up->color = RED;
				rbt_leftRotate(t, z->up->up);
			} 
		} 
	} 
	t->root->color = BLACK;
} 


void rbt_insert(rbt_tree* t, rbt_node* z){
	rbt_node* y = t->nil;
	rbt_node* x = t->root;
	
	while(x != t->nil){
		y = x;
		if((t->cmpfunc(z->data, x->data)) < 0)
			x = x->left;
		else
			x = x->right;
	} 
	z->up = y;
	if(y == t->nil)
		t->root = z;
	else if((t->cmpfunc(z->data, y->data)) < 0)
		y->left = z;
	else
		y->right = z;

	z->right = t->nil;
	z->left = t->nil;
	z->color = RED;
	rbt_insertFix(t, z);
	
} 

rbt_node* rbt_minimum(rbt_tree *t, rbt_node *x){
	while(x->left != t->nil)
		x = x->left;
	return x;
}


void rbt_deleteFix(rbt_tree *t, rbt_node* x){
	rbt_node* w;
	while(x != t->root && x->color == BLACK){
			
		if(x == x->up->left){
			w = x->up->right;

			if(w->color == RED){
				w->color = BLACK;
				x->up->color = RED;
				rbt_leftRotate(t, x->up);
				w = x->up->right;
			} 

			if(w->left->color == BLACK && w->right->color == BLACK){ 
				w->color = RED;
				x = x->up;
			}else{
				if(w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					rbt_rightRotate(t, w);
					w = x->up->right;
				} 
				w->color = x->up->color;
				x->up->color = BLACK;
				x->right->color = BLACK;
				rbt_leftRotate(t, x->up);
				x = t->root;
			} 
		}else{
			w = w->up->left;

			if(w->color == RED){
				w->color = BLACK;
				x->up->color = RED;
				rbt_rightRotate(t, x->up);
				w = x->up->left;
			} 

			if(w->right->color == BLACK && w->left->color == BLACK){ 
				w->color = RED;
				x = x->up;
			}else{
				if(w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					rbt_leftRotate(t, w);
					w = x->up->left;
				} 
				w->color = x->up->color;
				x->up->color = BLACK;
				x->left->color = BLACK;
				rbt_rightRotate(t, x->up);
				x = t->root;
			}
		} 
	} 
	x->color = BLACK;
} 


void rbt_delete(rbt_tree *t, rbt_node *z){
	rbt_node *y = z;
	rbt_node *x;
	color y_original = y->color;

	if(z->left == t->nil){
		x = z->right;
		rbt_transplant(t, z, z->right);
	}else if(z->right == t->nil){
		x = z->left;
		rbt_transplant(t, z, z->left);
	}else{
		y = rbt_minimum(t, z->right);
		y_original = y->color;
		x = y->right;

		if(y->up == z){
			x->up = z;
		}else{
			rbt_transplant(t, y, y->right);
			y->right = z->right;
			y->right->up = y;
		} 
		rbt_transplant(t, z, y);
		y->left = z->left;
		y->left->up = y;
		y->color = z->color;
	} 
	free(z);
	if(y_original == BLACK)
		rbt_deleteFix(t, x);
}

void rbt_transplant(rbt_tree* t, rbt_node* u, rbt_node* v){
	if(u->up == t->nil)
		t->root = v;
	else if(u == u->up->left)
		u->up->left = v;
	else
		u->up->right = v;
	v->up = u->up;
}

void rbt_freeNode(rbt_tree *t, rbt_node *n){
	if(n == t->nil || n == NULL)
		return;
	rbt_freeNode(t, n->left);
	rbt_freeNode(t, n->right);
	free(n);
}

void rbt_free(rbt_tree *t){
	rbt_freeNode(t, t->root);	
	rbt_freeNode(t, t->nil);
	free(t);
}

void inorder(rbt_tree* t, rbt_node* n){
	if(n == t->nil)
		return;

	inorder(t, n->left);
	printf("%d\n", *(int*)(n->data));
	inorder(t, n->right);
}























