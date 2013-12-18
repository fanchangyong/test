#include <stdlib.h>

void merge(int* arr,int lo,int mid,int hi)
{
	int len=hi-lo+1;
	int* carr=malloc(sizeof(int)*len);
	int i,j,k;
	for(i=lo;i<hi+1;++i)
	{
		carr[i]=arr[i];
	}
	
	i=lo;
	j=lo;
	k=mid+1;
	for(;;)
	{
		if(i>=hi+1)
		{
			break;
		}
		if(j>=mid+1)
		{
			arr[i]=carr[k];
			++k;
		}
		else if(k>=hi+1)
		{
			arr[i]=carr[j];
			++j;
		}
		else
		{
			if(carr[j]<=carr[k])
			{
				arr[i]=carr[j];
				++j;
			}
			else
			{
				arr[i]=carr[k];
				++k;
			}
		}
		++i;
	}
	free(carr);
}
