#include <stdio.h>
#include <stdlib.h>

int count;

int find(int* ids,int p)
{
	return ids[p];
}

int connected(int* ids,int p,int q)
{
	return find(ids,p)==find(ids,q);
}

void un(int* ids,int len,int p,int q)
{
	if(ids[p]==ids[q])
		return;

	int i;
	int pid=ids[p];
	int qid=ids[q];
	for(i=0;i<len;++i)
	{
		if(ids[i]==pid)
		{
			ids[i]=qid;
		}
	}
	--count;
}

int main()
{
	int len;
	scanf("%d",&len);
	printf("len:%d\n",len);

	int* ids=malloc(sizeof(int)*len);
	int i;
	for(i=0;i<len;++i)
	{
		ids[i]=i;
		++count;
	}
	for(;;)
	{
		int a,b;
		int ret=scanf("%d %d",&a,&b);
		if(ret==EOF)
		{
			break;
		}
		else if(ret==0)
		{
			fpurge(stdin);
			continue;
		}
		else
		{
			un(ids,len,a,b);
		}
	}
	printf("Count:%d\n",count);
}


