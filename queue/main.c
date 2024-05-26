#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "queue.h"

//单元测试
int main(void) {
	Queue* q = queue_create();
	
	queue_push(q, 1);
	queue_push(q, 2);
	queue_push(q, 3);
	queue_push(q, 4);

	return 0;
}
