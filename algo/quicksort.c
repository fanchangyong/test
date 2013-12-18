#include <stdio.h>

void exch(int* arr,int i,int j);

int partition(int* arr,int lo,int hi)
{
	int v=arr[lo];
	int i=lo;
	int j=hi+1;
	for(;;)
	{
		while(arr[++i]<v)
		{
			if(i>=hi)
				break;
		}
		while(arr[--j]>v)
		{
			if(j<=lo)
				break;
		}
		if(i>=j)
			break;
		exch(arr,i,j);
	}
	exch(arr,lo,j);
	return j;
}

void exch(int* arr,int i,int j)
{
	int t=arr[i];
	arr[i]=arr[j];
	arr[j]=t;
}

void qsort(int* arr,int lo,int hi)
{
	if(lo>=hi)
		return;
	int m=partition(arr,lo,hi);
	qsort(arr,lo,m-1);
	qsort(arr,m+1,hi);
}

int main()
{
#define LEN 100
	int arr[LEN];
	int i;
	for(i=0;i<LEN;++i)
	{
		arr[i]=LEN-i;
	}
	qsort(arr,0,LEN-1);
	for(i=0;i<LEN;++i)
		printf("%d,",arr[i]);

	printf("\n");
	return 0;
}
