#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
	int v;
	struct node* left;
	struct node* right;
};

typedef struct node node;


node* create_node(int v)
{
	node* pn = malloc(sizeof(node));
	pn->v=v;
	pn->left=0;
	pn->right=0;
	return pn;
}

node* create_tree()
{
	return create_node(0);
}

void put(node* root,int v)
{
	if(v>=root->v)
	{
		if(root->right!=0)
			put(root->right,v);
		else
			root->right=create_node(v);
	}
	else if(v<root->v)
	{
		if(root->left!=0)
			put(root->left,v);
		else
			root->left=create_node(v);
	}
}

int minimum(node* root)
{
	if(root->left!=0)
	{
		return minimum(root->left);
	}
	return root->v;
}

int maximum(node* root)
{
	if(root->right!=0)
		return maximum(root->right);
	return root->v;
}

void delete(node* root,int v)
{
	
}

void traverse(node* root)
{
	if(root==0)
	{
		return;
	}
	traverse(root->left);
	printf("%d,",root->v);
	traverse(root->right);
}

int max(int a,int b)
{
	return a>b?a:b;
}

int height(node* root,int n)
{
	if(root==0)
		return n;
	return max(height(root->left,n+1),height(root->right,n+1));
}

int has(node* root,int n)
{
	if(root==0)
		return 0;
	if(root->v==n)
		return 1;
	return has(root->left,n) || has(root->right,n);
}

node* successor(node* root)
{
	// todo
	return 0;
}

int main(int argc,char** argv)
{
	node* root=create_tree();	
	put(root,50);
	put(root,40);
	put(root,45);
	put(root,30);
	put(root,60);
	put(root,55);
	put(root,65);
	put(root,25);
	put(root,35);
	put(root,54);
	put(root,56);
	traverse(root);
	printf("\n");
	int h=height(root,0);
	int m=minimum(root->right);
	int max=maximum(root->right);
	printf("minimum:%d,max:%d\n",m,max);
	return 0;
}
