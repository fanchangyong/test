/*
 * Reverse a single linked list
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
	struct node* next;
	int n;
};

node* create_node()
{
	node* pn=malloc(sizeof(node));
	pn->next=0;
	pn->n=0;
	return pn;
}

node* reverse(node* head)
{
	node* tmp_node=head;
	node* new_head=NULL;
	node* prev_node=NULL;
	node* cur_node=NULL;
	while(tmp_node!=NULL)
	{
		cur_node=tmp_node;
		new_head=tmp_node;
		tmp_node=tmp_node->next;
		cur_node->next=prev_node;
		prev_node=cur_node;
	}
	return new_head;
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

	printf("Before Reverse:\n");
	node* head=nodes[0];
	while(head)
	{
		printf("node:%p,next:%p\n",head,head->next);
		head=head->next;	
	}
	node* new_head=reverse(nodes[0]);
	printf("\nAfter Reverse:\n");
	while(new_head)
	{
		printf("node:%p,next:%p\n",new_head,new_head->next);
		new_head=new_head->next;
	}

	return 0;
}
