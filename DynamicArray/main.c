#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Vector.h"

//单元测试
int main(void) {
	//创建空的动态数组
	Vector* v = vector_create();

	for (int i = 0; i < 200; i++) {
		push_back(v, i);
	}

	vector_destroy(v);

	return 0;
}
