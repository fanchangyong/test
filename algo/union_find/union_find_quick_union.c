#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count=0;

int find(int *arr,int n)
{
	while(arr[n]!=n)
		n=arr[n];
	return n;
}

int connected(int *arr,int p,int q)
{
	return find(arr,p) == find(arr,q);
}

void un(int* lens,int* arr,int p,int q)
{
	int proot=find(arr,p);
	int qroot=find(arr,q);
	if(proot==qroot)
	{
		printf("** Already connected:%d,%d,doesn't need to union\n",p,q);
		return;
	}
	printf("## Union %d and %d,root:%d,%d\n",p,q,proot,qroot);
	if(lens[proot]<=lens[qroot])
	{
		arr[proot]=qroot;
		lens[qroot]+=lens[proot];
	}
	else
	{
		arr[qroot]=proot;
		lens[proot]+=lens[qroot];
	}
	--count;
}

int main(int argc,char** argv)
{
	int len;
	scanf("%d",&len);
	int *ids=malloc(sizeof(int)*len);
	int *lens=malloc(sizeof(int)*len);
	int i;
	for(i=0;i<len;++i)
	{
		ids[i]=i;
		lens[i]=1;
		++count;
	}

	for(;;)
	{
		int a,b;
		int ret=scanf("%d %d",&a,&b);
		if(ret==0)
		{
			fpurge(stdin);
			continue;
		}
		else if(ret==EOF)
		{
			break;
		}
		else
		{
			un(lens,ids,a,b);
		}
	}
	printf("$$$$$$Count is:%d\n",count);
}

