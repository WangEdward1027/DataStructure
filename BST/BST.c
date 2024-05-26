// BST.c
#include "BST.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

BST* bst_create(void) {
	return calloc(1, sizeof(BST));
}

void destroy(TreeNode* root) {  //后序遍历实现释放
	//边界条件
	if (root == NULL) {
		return;
	}
	//递归公式：左右根
	destroy(root->left);
	destroy(root->right);
	free(root);            // 释放根节点
}

//析构函数1:委托 + 后序遍历
void bst_destroy(BST* tree) {
	//0.错误处理
	if (tree == NULL) {
		printf("tree == NULL, destroy failed.\n");
		return;
	} 
	//1.释放树的结点【委托(外包)】 
	destroy(tree->root);
	//2.释放BST结构体
	free(tree);
}

//析构函数2:层序遍历
void bst_destroy_2(BST* tree) {
	//容错处理
	if (!tree || !tree->root)  return;
	//层序遍历
	Queue* queue = queue_create();
	queue_push(queue, tree->root);          // 将根结点入队列
	while (!queue_empty(queue)) {           // 判断队列是否为空	
		TreeNode* node = queue_pop(queue);  // 出队列，销毁这个节点
		if (node->left) {
			queue_push(queue, node->left);
		}
		if (node->right) {
			queue_push(queue, node->right);
		}
		free(node);                         // 释放节点
	}
	free(tree);							    // 节点销毁
}

//添加结点：若 key 结点已存在，则什么也不做。若 key 不存在，则添加该 key 结点
void bst_insert(BST* tree, K key) {
	// 1. 找到添加的位置
	TreeNode* parent = NULL;
	TreeNode* curr = tree->root;

	int cmp;
	while (curr) {
		cmp = key - curr->key;
		if (cmp < 0) {           //目标值 < 当前值
			parent = curr;		 //前驱指针(父指针)跟上
			curr = curr->left;	 //curr向左走
		}
		else if (cmp > 0) {	     //目标值 > 当前值
			parent = curr;		 //前驱指针(父指针)跟上
			curr = curr->right;  //curr向右走
		}
		else {                   //目标值 = 当前值
			return;				 //已经有该值了，不可重复插入，直接返回
		}
	}	// curr == NULL, cmp = key - parent->key ？？？
	// 2. 添加节点
	// a. 创建节点并初始化
	TreeNode* newnode = calloc(1, sizeof(TreeNode));
	newnode->key = key;
	// b. 链接
	if (parent == NULL) {
		tree->root = newnode;
	}
	else if (cmp < 0) {
		parent->left = newnode;
	}
	else {
		parent->right = newnode;
	}
}

TreeNode* bst_search(BST* tree, K key) {
	TreeNode* curr = tree->root; //申请一个树结点指针，指向根结点
	while (curr) {
		int cmp = key - curr->key;
		if (cmp < 0) {			 //目标值 < 当前值
			curr = curr->left;   //向左走
		}
		else if (cmp > 0) {      //目标值 > 当前值
			curr = curr->right;  //向右走 
		}
		else {					 //目标值 = 当前值
			return curr;	     //找到目标，返回当前树结点指针
		}
	} // curr == NULL
	return NULL;				 //未找到目标，返回空指针
}

void bst_delete(BST* tree, K key) {
	// 1. 找到删除的节点
	TreeNode* parent = NULL;
	TreeNode* curr = tree->root;
	while (curr) {
		int cmp = key - curr->key;
		if (cmp < 0) {
			parent = curr;
			curr = curr->left;
		}
		else if (cmp > 0) {
			parent = curr;
			curr = curr->right;
		}
		else {
			break;
		}
	} // curr == NULL || curr != NULL
	if (curr == NULL) return;
	// 2. 删除 curr 节点
	if (curr->left && curr->right) {
		// 退化成度为0或者度为1的情况
		TreeNode* minp = curr;
		TreeNode* min = curr->right;
		while (min->left) {
			minp = min;
			min = min->left;
		}
		// 退化
		curr->key = min->key;
		curr = min;
		parent = minp;
	}

	// 找到唯一的孩子
	TreeNode* child = curr->left ? curr->left : curr->right;

	if (parent == NULL) {
		tree->root = child;
	}
	else {
		// 将child链接到parent的正确位置
		int cmp = curr->key - parent->key;	// Caution: 得重新比较
		if (cmp < 0) {
			parent->left = child;
		}
		else if (cmp > 0) {
			parent->right = child;
		}
		else {
			// Caution: 可能cmp == 0
			parent->right = child;
		}
	}
	free(curr);
}

// 深度优先遍历
void preorder(TreeNode* root) {
	//边界条件
	if (root == NULL) {
		return;
	}
	//递归公式：根左右
	printf("%d", root->key);
	preorder(root->left);
	preorder(root->right);
}

//先根遍历：委托(外包)
void bst_preorder(BST* tree) {
	preorder(tree->root);
	printf("\n");
}

void inorder(TreeNode* root) {
	// 边界条件
	if (root == NULL) {
		return;
	}
	// 递归公式: 左根右
	inorder(root->left);       // 遍历左子树
	printf("%d ", root->key);  // 遍历根结点
	inorder(root->right);      // 遍历右子树
}

//中序遍历：委托(外包)
void bst_inorder(BST* tree) {
	inorder(tree->root);
	printf("\n");
}

void postorder(TreeNode* root) {
	//边界条件
	if (root == NULL) {
		return;
	}
	//递归公式：左右根
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->key);
}

//后序遍历：委托(外包)
void bst_postorder(BST* tree) {
	postorder(tree->root);
	printf("\n");
}

// 广度优先遍历:层序遍历
void bst_levelorder(BST* tree) {
	Queue* q = queue_create();
	queue_push(q, tree->root);  	    //根结点入队列
	while (!queue_empty(q)) {		    //判断队列是否为空
		TreeNode* node = queue_pop(q);  //队头结点出队并遍历
		printf("%d ", node->key);
		if (node->left) 	queue_push(q, node->left);
		if (node->right)	queue_push(q, node->right);
	} 
}

//分层打印：实现1
void bst_levelorder_fenceng1(BST* tree) {
	Queue* q = queue_create();
	queue_push(q, tree->root);
	
	int cur_count = 1; //当前层的结点数目
	int next_count = 0;//下一层的结点数目

	while (!queue_empty(q)) {
		TreeNode* node = queue_pop(q);
		cur_count--;
		printf("%d ", node->key);
		
		if (node->left) {
			queue_push(q, node->left);
			next_count++;
		}
		if (node->right) {
			queue_push(q, node->right);
			next_count++;
		}

		//分层打印
		if (cur_count == 0) {
			printf("\n");
			cur_count = next_count;
			next_count = 0;
		}
	}
	printf("\n");
}

void bst_levelorder_fenceng2(BST* tree) {
	Queue* q = queue_create();
	queue_push(q, tree->root);

	while (!queue_empty(q)) {
		int size = q->size;       //记录当前层的结点数
		for (int i = 0; i < size; i++) {
			TreeNode* node = queue_pop(q);
			printf("%d ", node->key);
			if (node->left) {
				queue_push(q, node->left);
			}
			if (node->right) {
				queue_push(q, node->right);
			}
		}
		printf("\n");
	}
	printf("\n");
}
