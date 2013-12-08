#include "inc.h"

void insert_sort(int *arr ,int n)
{
	int i;
	for(i=1;i<n;++i)
	{
		int key=arr[i];
		int j=i-1;
		while(j>=0)
		{
			if(key<arr[j])
			{
				arr[j+1]=arr[j];
			}
			else
			{
				arr[j+1]=key;
				break;
			}
			if(j==0)
			{
				arr[j]=key;
				break;
			}
			--j;
		}
	}
}

int main()
{
	int arr[]={54,64,38,29,35,11,5,251,4,3,2,1};
	int len=sizeof(arr)/sizeof(int);
	printf("len:%d\n",len);
	insert_sort(arr,len);
	int i;
	printf("len:%d\n",len);
	for(i=0;i<len;++i)
	{
		printf("%d,",arr[i]);
	}
	printf("\n");
}
