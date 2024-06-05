#include "List.h"
#include <stdio.h>
#include <stdlib.h>

//API
List* list_create(void) {
	return calloc(1, sizeof(List));
}

void list_destroy(List* list) {
	Node* cur = list->head;
	while (cur != NULL) {
		Node* next = cur->next;
		free(cur);
	}
	free(list);
}

//头插法
void add_before_head(List* list, E val) {
	//1.创建新结点
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Error: malloc failed in add_before_head\n");
		exit(1);
	}
	//2.初始化结点
	new_node->data = val;
	new_node->next = list->head;
	//3.更新链表的信息
	list->head = new_node;	   //更新链表的头指针
	if (list->tail == NULL) {
		list->tail = new_node;
	}
	list->size++;
}

//尾插法
void add_behind_tail(List* list, E val) {
	//1.创建新结点
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Error: malloc failed in add_behind_tail\n");
		exit(1);
	}
	//2.初始化结点
	new_node->data = val;
	new_node->next = NULL;
	//3.链接并更新链表信息
	if (list->tail == NULL) {
		list->head = new_node;
		list->tail = new_node;
	}else{
		list->tail->next = new_node;
		list->tail = new_node;
	}
	list->size++;
}

//任意位置插入结点
void add_node(List* list, int idx, E val) {
	//位置参数检查
	if (idx < 0 || idx > list->size) {
		printf("Illegal Argument: idx = %d, size = %d\n", idx, list->size);
		exit(1);
	}
	//头插
	if (idx == 0) { 
		add_before_head(list, val);
		return;
	}
	//尾插
	if (idx == list->size) { 
		add_behind_tail(list,val);
		return;
	}
	//链表中间插入
	Node* curr = list->head;
	for (int i = 0; i < idx - 1; i++) {
		curr = curr->next;
	}
	//在curr的后面添加结点
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Error: malloc failed in add_behind_tail\n");
		exit(1);
	}
	new_node->data = val;
	new_node->next = curr->next;
	curr->next = new_node;
	list->size++;
}

// 删除第一个值与val相等的结点
void delete_node(List* list, E val) {
	Node* prev = NULL;
	Node* curr = list->head;

	// 找到第一个值与val相等的结点
	while (curr) {
		if (curr->data == val) {
			// 删除curr结点
			if (prev == NULL) {
				// 删除第一个结点
				list->head = curr->next;
				if (list->tail == curr) {
					list->tail = NULL;
				}
			}
			else {
				prev->next = curr->next;
				if (list->tail == curr) {
					list->tail = prev;
				}
			}
			list->size--;
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	} // curr == NULL
}

// 查找第一个与指定值相等的结点
Node* search_for_value(List* list, E val) {
	Node* curr = list->head;
	while (curr) {
		if (curr->data == val) {
			return curr;
		}
		curr = curr->next;
	} // curr == NULL
	return NULL;
}

// 根据索引查找值
Node* find_by_index(List* list, int idx) {
	// 参数校验
	if (idx < 0 || idx >= list->size) {
		printf("Illegal Argument: idx=%d, size=%d\n", idx, list->size);
		exit(1);
	}
	// 循环不变式：curr指向结点的索引为i
	Node* curr = list->head;
	for (int i = 0; i < idx; i++) {
		curr = curr->next;
	} // i == idx
	return curr;
}
