#include <stdio.h>
#include <stdlib.h>

// 用另一个链表来存储出现过的node地址，如果同一个地址出现多于1次，表示有循环

typedef struct node node;

struct node
{
	struct node* next;
	int n;
};

struct node_count
{
	struct node* node;
	int count;
	struct node_count* next;
};

typedef struct node_count node_count;

int add_node(node_count* record,node* node)
{
	printf("add_node,record:%p,node:%p\n",record,node);
	node_count* record_tmp=record;
	while(record_tmp!=NULL)
	{
		if(record_tmp->node==node)
		{
			record_tmp->count++;
			return 1;
		}
		if(record_tmp->next==NULL)
		{
			node_count* new_record=malloc(sizeof(node_count));
			new_record->node=node;
			new_record->count=1;
			new_record->next=NULL;
			record_tmp->next=new_record;
			return 0;
		}
		record_tmp=record_tmp->next;
	}

	return 0;
}

int has_cycle(node* first)
{
	if(first==NULL)
	{
		return 0;
	}
	node_count* record=malloc(sizeof(node_count));
	record->node=NULL;
	record->next=NULL;
	record->count=0;

	node* pn=first;
	while(pn)
	{
		printf("pn:%p\n",pn);
		if(add_node(record,pn))
		{
			return 1;
		}
		pn=pn->next;
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

	nodes[4]->next=nodes[1];

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
