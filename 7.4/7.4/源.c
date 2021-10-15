#include<stdio.h>
#include<stdlib.h>
typedef struct bstnode
{
	int element;
	int bf;
	struct bstnode* lchild, * rchild;
}BSTNode,*BSTree;
