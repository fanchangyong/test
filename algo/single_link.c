#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct node
{
	int v;
	struct node *next;
};

typedef struct node node;

node* create_node(int n)
{
	node* pn=malloc(sizeof(node));
	pn->v=n;
	pn->next=NULL;
	return pn;
}

void link_insert(node* link,int n)
{
	node* pn=malloc(sizeof(node));
	pn->v=n;
	pn->next=NULL;

	node* t=link;
	while(t->next!=NULL)
	{
		t=t->next;
	}
	t->next=pn;
}

void link_empty(node** link)
{
	node* t=*link;
	while(t!=NULL)
	{
		node* ct=t;
		t=ct->next;
		free(ct);
	}
	*link=NULL;
}

void link_dump(node* link)
{
	node* t=link;
	while(t!=NULL)
	{
		printf("%d,",t->v);
		t=t->next;	
	}
	printf("\n");
}

int link_remove(node** link,int n)
{
	node* t=*link;
	if(t->v==n)	
	{
		// remove head
		*link=t->next;
		free(t);
		return 1;
	}
	while(t->next!=NULL)
	{
		node* p1=t;
		node* p2=t->next;
		if(p2->v==n)
		{
			// remove p2
			p1->next=p2->next;
			free(p2);
			return 1;	
		}
		t=t->next;
	}
	return 0;
}

int link_find(node* link,int n)
{
	node* t=link;
	int pos=0;
	while(t!=NULL)
	{
		if(t->v==n)
			return pos;
		t=t->next;
		++pos;
	}
	return -1;
}

int main()
{
	node* p=create_node(1);
	link_insert(p,10);
	link_insert(p,20);
	link_insert(p,30);
	link_remove(&p,1);
	link_empty(&p);
	if(p==NULL)
	{
		printf("empty ok\n");
	}
	else 
	{
		printf("empty error\n");
	}
	return 0;
}
