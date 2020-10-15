/*********************************************************************
 * Author: Zournatzis Dimitrios
 * Generic data type Red Black Tree implementation in C
 * Based on textbook: "Introduction to Algorithms - Cormen, Leiserson, 
 * 													Rivest, Stein
 *
 * file: red_black_tree.h
 *********************************************************************
*/
#ifndef _RBT_
#define _RBT_

typedef int (*cmpr_f)(void* a, void* b);

typedef
enum color_e{
	BLACK, RED
}color;

typedef 
struct rbt_node_s{
	void* data;
	struct rbt_node_s *left;
	struct rbt_node_s *right;
	struct rbt_node_s *up;
	color color;
}rbt_node;

typedef
struct rbt_tree_s{
	rbt_node* root;
	rbt_node* nil;
	cmpr_f cmpfunc;
}rbt_tree;

/*Init and create redblacktree*/
rbt_tree *rbt_init(cmpr_f cmpfunc);
rbt_node *rbt_newNode(void* data, size_t data_size); 
void rbt_leftRotate(rbt_tree* t, rbt_node* x);
void rbt_rightRotate(rbt_tree* t, rbt_node* x);
void rbt_insertFix(rbt_tree* t, rbt_node* z);
void rbt_insert(rbt_tree* t, rbt_node* z);
void rbt_deleteFix(rbt_tree *t, rbt_node* x);
void rbt_delete(rbt_tree *t, rbt_node *z);
void rbt_transplant(rbt_tree* t, rbt_node* u, rbt_node* v);
void rbt_freeNode(rbt_tree *t, rbt_node *n);
void rbt_free(rbt_tree *t);
void inorder(rbt_tree* t, rbt_node* n);

#endif /*_RBT_*/
