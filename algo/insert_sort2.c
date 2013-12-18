#include <stdio.h>

void exch(int* arr,int i,int j)
{
	int t=arr[i];
	arr[i]=arr[j];
	arr[j]=t;
}

void sort(int* arr,int len)
{
	int i,j;
	for(i=1;i<len;++i)
	{
		for(j=i;j>0;j--)
		{
			if(arr[j]<arr[j-1])
				exch(arr,j,j-1);
			else
				break;
		}
	}
}

int main()
{
#define LEN 10
	int arr[LEN];
	int i;
	for(i=0;i<LEN;++i)
		arr[i]=LEN-i;
	sort(arr,LEN);

	for(i=0;i<LEN;++i)
		printf("%d,",arr[i]);
	printf("\n");
	return 0;
}
