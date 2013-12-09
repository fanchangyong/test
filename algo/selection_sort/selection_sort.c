#include <stdio.h>

void selection_sort(int *arr,int len)
{
	int i;
	int j;
	for(i=0;i<len;++i)
	{
		int min=i;
		for(j=i;j<len;++j)
			if(arr[j]<arr[min])
				min=j;

		int t=arr[i];
		arr[i]=arr[min];
		arr[min]=t;
	}
}

int main(int argc,char** argv)
{
	int arr[]={5,25,4,84,3,6,2,1};
	int len=sizeof(arr)/sizeof(int);
	selection_sort(arr,len);
	int i;
	for(i=0;i<len;++i)
		printf("%d,",arr[i]);

	printf("\n");
	return 0;
}
