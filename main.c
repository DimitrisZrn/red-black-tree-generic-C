#include <stdio.h>
#include "red_black_tree.h"

int cmpr(void* a, void* b){
	int a1 = (*(int*)a);
	int b1 = (*(int*)b);
	return (a1-b1);
} 
int main(){
	rbt_tree *tree = rbt_init(cmpr);
	int y=30;	
	rbt_node* oof = rbt_newNode(&y, sizeof(int));
	rbt_insert(tree, oof);
	rbt_node* new;
	for(int i=0; i<20; i++){
		y = i;
		new = rbt_newNode(&y, sizeof(int));
		rbt_insert(tree, new);

	} 
	inorder(tree, tree->root);
	printf("==================\n");
	rbt_delete(tree, oof);
	inorder(tree ,tree->root);
	
	rbt_free(tree);
} 
