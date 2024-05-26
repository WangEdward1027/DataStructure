#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>  //malloc

#define DEFAULT_CAPACITY 8
#define PREALLOC_MAX 1024

//构造函数
Vector* vector_create(void) {
	Vector* v = malloc(sizeof(Vector));
	if (v == NULL){
		printf("Error: malloc failed in cector_create\n");
		exit(1);
	}
	E* p = malloc(DEFAULT_CAPACITY * sizeof(E));
	if (!p) {  //p == NULL
		free(v);
		printf("Error: malloc failed in vector_create\n");
		exit(1);
	}

	v->elements = p;
	v->capacity = DEFAULT_CAPACITY;
	v->size = 0;
	return v;
}

//析构函数
void vector_destroy(Vector* v) {
	//按构造的相反顺序进行析构
	free(v->elements);
	free(v);
}

void grow_capacity(Vector* v) {
	int new_capacity = v->capacity < PREALLOC_MAX ?
	      	v->capacity << 1 : v->capacity + PREALLOC_MAX;

	//realloc返回重新分配的内存的指针
	E* p = realloc(v->elements, new_capacity * sizeof(E));
	//重新分配内存失败
	if (p == NULL) {
		printf("Error: realloc failed in grow_capacity\n");
		exit(1);
	}
	//重新分配内存成功
	//更改动态数组的属性
	v->elements = p;
	v->capacity = new_capacity;
}

//请实现push_back方法
void push_back(Vector* v, E val) {
	//判断是否需要扩容
	if (v->capacity == v->size) {
		grow_capacity(v);
	}
	v->elements[v->size] = val;
	v->size++;
}
