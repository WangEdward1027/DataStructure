#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"
#include <stdio.h>

int main(void) {
	Stack* s = stack_create();

	stack_push(s,1);
	stack_push(s,2);
	stack_push(s,3);
	stack_push(s,4);

	stack_destroy(s);
	return 0;
}
