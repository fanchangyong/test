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

int size(node* head)
{
	int count=0;
	while(head!=NULL)
	{
		head=head->next;
		++count;
	}
	return count;
}

node* nth(node* head,int n)
{
	int count=0;
	while(head!=NULL)
	{
		if(count==n)
		{
			return head;
		}
		head=head->next;
		++count;
	}
	return NULL;
}

void print_list(node* head)
{
	while(head)
	{
		printf("node:%p,next:%p\n",head,head->next);
		head=head->next;
	}
}

node* nth_from_end(node* head,int n)
{
	int length=size(head);	
	return nth(head,length-n-1);
}

/*
 * Another Solution
 */
node* nth_from_end_2(node* head,int n)
{
	node* p1,*p2;
	p1=head;
	p2=head;
	int count=0;
	while(p1)
	{
		p1=p1->next;
		if(count>n)
		{
			return NULL;
		}
		if(count==n)
		{
			break;
		}
		++count;
	}
	while(p1!=NULL)
	{
		p1=p1->next;		
		p2=p2->next;
	}
	return p2;
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

	printf("List:\n");
	print_list(nodes[0]);

	node* head=nodes[0];
	node* n=nth_from_end_2(head,2);
	printf("\n:%p\n",n);

	return 0;
}
