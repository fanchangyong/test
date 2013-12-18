#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


cstack* create_stack(int n)
{
	cstack* stack=(cstack*)malloc(sizeof(cstack));
	stack->pos=0;
	stack->maxn=n;
	stack->pv=malloc(sizeof(void**)*n);
	return stack;
}

void push(cstack* stack,void* v)
{
	stack->pv[stack->pos++]=v;	
}

void* pop(cstack* stack)
{
	return stack->pv[--stack->pos];
}

int main111()
{
	cstack* st=create_stack(10);
	int n=1;
	push(st,&n);
	int*pn = pop(st);
	printf("n:%d\n",*pn);
	return 0;
}
