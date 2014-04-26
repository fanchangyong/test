#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("Usage:./a.out <len> <k>\n");
		return 1;
	}
	
	srandom(time(NULL));

	int len = atoi(argv[1]);
	int k = atoi(argv[2]);

	int* arr = malloc(sizeof(int)*len);
	int i;
	for(i=0;i<len;i++)
	{
		arr[i]=random()%100;
	}

	printf("Array is:\n");
	for(i=0;i<len;i++)
	{
		if(i<len-1)
			printf("%d,",arr[i]);
		else
			printf("%d",arr[i]);
	}
	printf("\n");

	int * arrk = malloc(sizeof(int)*k);
	for(i=0;i<k;i++)
	{
		arrk[i]=arr[i];
	}
	for(i = k;i < len;i++)
	{
		int j;
		int maxk=0;
		for(j=0;j<k;j++)
		{
			if(arrk[j] >arrk[maxk])
			{
				maxk=j;
			}
		}
		if(arr[i]<arrk[maxk])
		{
			arrk[maxk]=arr[i];
		}
	}

	printf("arrk:\n");
	int j;
	for(j=0;j<k;j++)
	{
		printf("%d,",arrk[j]);
	}
	printf("\n");
	return 0;
}
