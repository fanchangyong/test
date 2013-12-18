#include <stdio.h>

void exch(int* arr,int i,int j);

void sort(int* arr,int len)
{
	int h=1;
	while(h<len/3)
		h=h*3+1;

	while(h>=1)
	{
		printf("```H=%d\n",h);
		int i;
		for(i=h;i<len;++i)
		{
			printf("#####I=%d\n",i);
			int j;
			for(j=i;j>=h ;j-=h)
			{
				printf("comparint arr[%d] and arr[%d]\n",j,j-h);
				if(arr[j]<arr[j-h])
					exch(arr,j,j-h);
				else
					break;
			}
		}
		h=h/3;
	}
}

void exch(int* arr,int i,int j)
{
	int t=arr[i];
	arr[i]=arr[j];
	arr[j]=t;
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
