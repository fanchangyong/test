#include <stdio.h>


void pr(int* arr,int len);

void bubble(int* arr,int len)
{
	int i;
	int j;
	for(i=len-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int t=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=t;
			}
		}
		//pr(arr,len);
	}
}

void pr(int *arr,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("arr[%d]=%d,",i,arr[i]);

	printf("\n");
}

int main(int argc,char** argv)
{
	int arr[]={5,4,3,2,1};
	int len=sizeof(arr)/sizeof(int);
	bubble(arr,len);
	int i;
	for(i=0;i<len;i++)
	{
		printf("%d,",arr[i]);
	}
	return 0;
}
