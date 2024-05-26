#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 100
#define DEFAULT_SIZE 10

Queue* queue_create() {
	Queue* queue = calloc(1, sizeof(Queue));
	queue->elements = calloc(DEFAULT_SIZE, sizeof(E));
	queue->capacity = DEFAULT_SIZE;
	return queue;
}

void queue_destroy(Queue* q) {
	free(q->elements); //释放的是手动malloc的内容
	free(q);
}

//自动扩容
void grow_capacity(Queue* q) {
	if (q->size >= MAX_SIZE) {
		printf("Error: push failed, because queue size has reached MAX_SIZE.\n");
		printf("size = %d, capacity = %d, MAX_SIZE = %d\n", q->size, q->capacity, MAX_SIZE);
		exit(-1);
	}

	int new_capacity = (q->capacity << 1) < MAX_SIZE ? (q->capacity << 1) : MAX_SIZE;

	E* new_arr = calloc(new_capacity, sizeof(E));
	if (!new_arr) {
		printf("calloc failed of new_arr in grow_capacity.\n");
		exit(-1);
	}

	for (int i = 0; i < q->size; i++) {
		new_arr[i] = q->elements[q->front];
		q->front = (q->front + 1) % q->capacity;
	}
	
	E* temp = q->elements;
	free(temp);

	q->elements = new_arr;
	q->front = 0;
	q->rear = q->size;  //下一个要插入元素的位置，目前为空
	q->capacity = new_capacity;
}

void queue_push(Queue* q, E val) {
	if (q->size == q->capacity) {
		grow_capacity(q); //自动扩容
	}
	q->elements[q->rear] = val;
	q->rear = (q->rear + 1) % q->capacity;
	q->size++;
}

E queue_pop(Queue* q) {
	if (queue_empty(q)) {
		printf("Error: pop failed, because queue is empty.\n");
		exit(-1);
	}
	int ret_val = q->elements[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return ret_val;
}

E queue_peek(Queue* q) {
	if (queue_empty(q)) {
		printf("Error: peek failed, because queue is empty.\n");
		exit(-1);
	}
	return q->elements[q->front];
}

bool queue_empty(Queue* q) {
	return q->size == 0;
}
