#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
	struct node* next;
	int n;
};

int has_cycle(node* first)
{
	if(first==NULL)
		return 0;

	node* fast,*low;
	fast=first;
	low=first;

	for(;;)
	{
		if(fast==NULL)
		{
			return 0;
		}
		if(low==NULL)
		{
			return 0;
		}
		if(fast->next==NULL)
		{
			return 0;
		}
		fast=fast->next->next;
		low=low->next;
		if(fast==low)
		{
			return 1;
		}
	}
	return 0;
}

node* create_node()
{
	node* pn=malloc(sizeof(node));
	pn->next=0;
	pn->n=0;
	return pn;
}

int main()
{
	node* nodes[5];
	int i;
	for(i=0;i<5;++i)
	{
		nodes[i]=create_node();
		if(i!=0)
		{
			nodes[i-1]->next=nodes[i];
		}
	}

	nodes[4]->next=nodes[2];

	for(i=0;i<5;++i)
	{
		printf("node %d,self:%p,next:%p\n",i,nodes[i],nodes[i]->next);
	}

	if(has_cycle(nodes[0]))
	{
		printf("has cycle!\n");
	}
	else
	{
		printf("not has cycle!\n");
	}

	return 0;
}
