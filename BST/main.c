#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "BST.h"

int main(void) {
	//1.创建
	BST* tree = bst_create();

	//2.插入
	bst_insert(tree, 9);
	bst_insert(tree, 42);
	bst_insert(tree, 57);
	bst_insert(tree, 5);
	bst_insert(tree, 3);
	bst_insert(tree, 13);

	//3.查找
	 TreeNode* node1 = bst_search(tree, 42);
	 TreeNode* node2 = bst_search(tree, 9527);

	//4.删除
	// bst_delete(tree, 3);
	// bst_delete(tree, 5);
	bst_delete(tree, 9);

	//5.遍历
		//5(2)中序遍历
	 bst_inorder(tree);
		//5(4)层序遍历
	 //bst_levelorder(tree);
		//5(4)层序遍历：分层打印
	//bst_levelorder_fenceng1(tree);
	//bst_levelorder_fenceng2(tree);

	//6.销毁
	bst_destroy(tree);

	return 0;
}
