#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int find(int* ids,int p)
{
	return ids[p];
}

int connected(int* ids,int p,int q)
{
	return find(ids,p)==find(ids,q);
}

void un(int* ids,int p,int q)
{
	if(ids[p]==ids[q])
		return;

	int i;
	int pid=ids[p];
	int qid=ids[q];
	for(i=0;i<MAX;++i)
	{
		if(ids[i]==pid)
			ids[i]=qid;
	}
}

struct pair
{
	int p;
	int q;
};


int main()
{
	int ids[MAX];
	int i;
	for(i=0;i<MAX;++i)
		ids[i]=i;

	struct pair pairs[10];

	for(i=0;i<10;++i)
	{
		struct pair pr;
		pr.p=rand()% MAX;
		pr.q=rand()% MAX;
		pairs[i]=pr;
	}

	for(i=0;i<10;++i)
	{
		struct pair pr=pairs[i];
		if(connected(ids,pr.p,pr.q))
		{
			printf("%d and %d is connected\n",pr.p,pr.q);
		}
		else
		{
			printf("%d and %d is not connected\n",pr.p,pr.q);
			un(ids,pr.p,pr.q);
		}
	}

	printf("*************************\n");
	
	for(i=0;i<10;++i)
	{
		struct pair pr=pairs[i];
		if(connected(ids,pr.p,pr.q))
		{
			printf("%d and %d is connected\n",pr.p,pr.q);
		}
		else
		{
			printf("%d and %d is not connected\n",pr.p,pr.q);
			printf("ids[%d]=%d,ids[%d]=%d\n",pr.p,ids[pr.p],pr.q,ids[pr.q]);
		}
	}

	printf("Now ids is:\n");
	for(i=0;i<MAX;++i)
	{
		printf("%d,",ids[i]);
		if(i%10==0)
			printf("\n");
	}
	printf("\n");
	return 0;
}

