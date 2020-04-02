# red-black-tree-generic-C
Generic Data Type - Red Black Tree implementation in C  
Chapter 14 (Red Black Trees), Introduction to Algorithms, Second edition by Cormen, Leiserson, Rivest, Stein

# How to use
1) Your compare function must return an interger
```C
int mycmpr(void* a, void* b)
```
if mycmpr(...)<0 then a is less than b  
if mycmpr(...)=0 then a is equal to b  
if mycmpr(...)>0 then a is greater than b    

2) Initialize your red black tree with:
```C
rbt_tree* tree = rbt_tree rbt_init(mycmpr)
``` 

3) Enter data (ex intergers)
```C
int y = 1;
rbt_node* new = rbt_newNode(&y, sizeof(int));
rbt_insert(tree, new);  
```
you can also:
```C
rbt_insert(tree, rbt_newNode(&y, sizeof(int));
``` 

4) Delete data (if needed)
```C
rbt_delete(t, new);
``` 

5) Free allocated memory
```C
rbt_free(tree);
```
