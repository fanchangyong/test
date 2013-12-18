#include <stdio.h>

void exch(int* arr,int i,int j)
{
	int t=arr[i];
	arr[i]=arr[j];
	arr[j]=t;
}

void sort(int* arr,int len)
{
	int i;
	int j=0;
	for(;j<len;j++)
	{
		for(i=len-1;i>j;--i)
		{
			if(arr[i]<arr[i-1])
				exch(arr,i,i-1);
		}
	}
}

int main()
{
#define LEN 10
	int i;
	int arr[LEN];
	for(i=0;i<LEN;++i)
		arr[i]=LEN-i;
	sort(arr,LEN);
	for(i=0;i<LEN;++i)
		printf("%d,\n",arr[i]);
	printf("\n");
	return 0;
}
