#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* stack_create(void) {
	return calloc(1, sizeof(Stack));
}

void stack_destroy(Stack* s) {
	Node* curr = s->top;
	while (curr != NULL) {
		Node* next = curr->next;
		free(curr);
		curr = next;
	}
	free(s);
}

void stack_push(Stack* s, E val) {
	Node* push = calloc(1,sizeof(Node));
	if (push == NULL) {
		printf("Error: push failed because calloc failed.\n");
		exit(1);
	}
	push->next = s->top;
	push->data = val;
	s->top= push;
	s->size++;
}

E stack_pop(Stack* s) {
	if (stack_empty(s)) {
		printf("Error: stack is empty, pop failed.\n");
		exit(1);
	}
	Node* remove = s->top;
	s->top = s->top->next;
	int ret_value = remove->data;
	free(remove);
	s->size--;
	return ret_value;
}

E stack_peek(Stack* s) {
	if (stack_empty(s)) {
		printf("Error: peek failed because the stack is empty.\n");
		exit(1);
	}
	return s->top->data;
}

bool stack_empty(Stack* s) {
	return s->size == 0;
}
