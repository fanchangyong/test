// Binary Search Tree

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

node* find(node* tree,int n);

struct node
{
	int v;
	node* left;
	node* right;
	node* parent;
};

node* create_tree(int n)
{
	node* p=malloc(sizeof(node));
	p->v=n;
	p->left=NULL;
	p->right=NULL;
	p->parent=NULL;
	return p;
}

void insert(node* tree,int n)
{
	node* tmp=tree;
	if(find(tree,n)!=NULL)
	{
		return;
	}

	node* pn=malloc(sizeof(node));
	pn->v=n;
	pn->left=NULL;
	pn->right=NULL;

	for(;;)
	{
		if(n<tmp->v)
		{
			if(tmp->left==NULL)
			{
				tmp->left=pn;
				pn->parent=tmp;
				return;
			}
			tmp=tmp->left;
		}
		else
		{
			if(tmp->right==NULL)
			{
				tmp->right=pn;
				pn->parent=tmp;
				return;
			}
			tmp=tmp->right;
		}
	}
}

void delete_node(node* del_node,int n)
{
	node* parent=del_node->parent;
	if(del_node->left==NULL && del_node->right==NULL)
	{
		if(parent->left->v==n)
		{
			parent->left=NULL;
			free(del_node);
		}
		else if(parent->right->v==n)
		{
			parent->right=NULL;
			free(del_node);
		}
	}
	else if(del_node->left==NULL)
	{
		if(parent->left->v==n)
		{
			
		}
	}
	node* tmp=del_node;
	while(tmp->right!=NULL)
	{
		tmp->v=tmp->right->v;
		tmp=tmp->right;
	}
	free(tmp);
}

void delete(node* tree,int n)
{
	node* tmp=tree;
	while(tmp!=NULL)
	{
		if(tmp->v==n)
		{
			//delete_node(tree,tmp);
		}
	}
}

node* find(node* tree,int n)
{
	if(tree==NULL)
	{
		return NULL;
	}
	if(n==tree->v)
	{
		return tree;
	}
	if(n>tree->v)
	{
		return find(tree->right,n);
	}
	else
	{
		return find(tree->left,n);
	}

}

void traverse(node* tree)
{
	if(tree==NULL)
		return;
	traverse(tree->left);
	printf("v:%d\n",tree->v);
	traverse(tree->right);
}

int main()
{
	node* tree=create_tree(10);
	insert(tree,17);
	insert(tree,18);
	traverse(tree);

	node* n=find(tree,17);
	printf("find result:%p\n",n);
	return 0;
}
