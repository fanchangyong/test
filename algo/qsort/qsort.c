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
			if(i==hi)
				break;

		while(arr[--j]>v)
			if(j==lo)
				break;

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

void sort(int *arr,int lo,int hi)
{
	if(lo>=hi)
		return;
	int m=partition(arr,lo,hi);
printf("sort,lo:%d,m:%d,hi:%d\n",lo,m,hi);
	sort(arr,lo,m-1);
	sort(arr,m+1,hi);
}

int main(int argc,char** argv)
{
#define LEN 50
	int arr[LEN];
	int i;
	for(i=0;i<LEN;++i)
		arr[i]=LEN-i;

	sort(arr,0,LEN-1);

	for(i=0;i<LEN;++i)
		printf("%d,",arr[i]);

	printf("\n");
	return 0;
}
