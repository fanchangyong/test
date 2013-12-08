// double circle linked list implemention

#include <stdlib.h>
#include <stdio.h>

typedef struct node node;

struct node
{
	int v;
	node* prev;
	node* next;
};

typedef node list;

list* create_list(int n)
{
	list* p=malloc(sizeof(list));
	p->prev=p;
	p->next=p;
	p->v=n;
	return p;
}

void push(list* head,int n)
{
	list* prev=head->prev;

	node* pn=malloc(sizeof(node));
	pn->v=n;
	pn->next=head;
	pn->prev=prev;
	prev->next=pn;
	head->prev=pn;
}

void remove_node(list** head,int n)
{
	list* tmp=*head;
	if((*head)->v==n)
	{
		*head=(*head)->next;
		free(tmp);
		return;
	}
	for(;;)
	{
		if(tmp->v==n)
		{
			tmp->prev->next=tmp->next;
			tmp->next->prev=tmp->prev;
			free(tmp);
			return;
		}
		tmp=tmp->next;
		if(tmp==*head)
		{
			return;
		}
	}
}

int find(list* head,int n)
{
	list* tmp=head;
	int pos=0;
	do{
		if(tmp->v==n)
		{
			return pos;
		}
		++pos;
		tmp=tmp->next;
	}while(tmp!=head);
	return -1;
}

void dump(list* head)
{
	list* tmp=head;
	do
	{
		printf("%d,",tmp->v);
		tmp=tmp->next;
	}while(tmp!=head);
	printf("\n");
}

int main()
{
	list* head=create_list(11);
	push(head,12);
	push(head,13);
	push(head,14);
	push(head,15);
	remove_node(&head,14);
	dump(head);
	int pos=find(head,15);
	printf("pos=%d\n",pos);
	return 0;
}
