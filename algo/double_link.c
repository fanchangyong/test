// double link list implements

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
	int v;
	node* prev;
	node* next;
};

node* create_node(int n)
{
	node* p=malloc(sizeof(node));
	p->v=n;
	p->prev=NULL;
	p->next=NULL;
	return p;
}

void push_node(node* link,int n)
{
	node* p=create_node(n);
	node* t=link;
	while(t->next!=NULL)
	{
		t=t->next;
	}
	t->next=p;
	p->prev=t;
}

void remove_node(node** link,int n)
{
	node* t=*link;
	if(t->v==n)
	{
		*link=t->next;
		free(t);
		return;
	}
	while(t->next!=NULL)
	{
		node* p=t->next;
		if(p->v==n)
		{
			p->prev->next=p->next;
			p->next->prev=p->prev;
			free(p);
			return;
		}
		t=t->next;
	}
}

void dump_link(node* link)
{
	while(link!=NULL)
	{
		printf("%d,",link->v);
		link=link->next;
	}
	printf("\n");
}

int main()
{
	node* head=create_node(1);
	push_node(head,10);
	push_node(head,30);
	push_node(head,40);
	remove_node(&head,20);
	remove_node(&head,1);
	remove_node(&head,30);
	dump_link(head);
	return 0;
}
