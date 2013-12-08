#include <stdio.h>

int bin_search(int* arr,int len,int n)
{
	int p1=0;
	int p2=len-1;
	for(;;)
	{
		if(p1>p2)
		{
			break;
		}
		int m=(p2+p1)/2;
		if(n<arr[m])
		{
			p2=m-1;
		}
		else if(n>arr[m])
		{
			p1=m+1;
		}
		else
		{
			return m;
		}
	}
	return -1;	
}

int main()
{
#define LEN 10
	int arr[LEN]={1,2,3,4,5,6,7,8,9,10};
	int pos=bin_search(arr,LEN,5);
	printf("pos=%d\n",pos);
	pos=bin_search(arr,LEN,50);
	printf("pos=%d\n",pos);
	return 0;
}
