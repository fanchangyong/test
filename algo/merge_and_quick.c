#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void exch(int* arr,int i,int j)
{
	int tmp=arr[i];
	arr[i]=arr[j];
	arr[j]=tmp;
}

int part(int* arr,int lo,int hi)
{
	int pivot=(lo+hi)/2;
	int i=lo;
	int j=hi;
	for(;;)
	{
		while(i<hi)
		{
			if(arr[i]>=arr[pivot])
			{
				break;
			}
			++i;
		}

		while(j>lo)
		{
			if(arr[j]<=arr[pivot])
			{
				break;
			}
			--j;
		}

		if(i>=j)
			break;

		exch(arr,i,j);
	}
	exch(arr,j,pivot);
	return j;
}

void merge(int* arr,int lo,int mid,int hi)
{
	int* aux_arr=malloc(hi-lo+1);
	int i;
	int j;
	for(i=lo;i<=hi;++i)
	{
		aux_arr[i]=arr[i];
	}
	i=lo;
	j=mid+1;
	int k;
	for(k=lo;k<=hi;++k)
	{
		if(i>mid)
		{
			arr[k]=aux_arr[j++];
		}
		else if(j>hi)
		{
			arr[k]=aux_arr[i++];
		}
		else if(aux_arr[i]<aux_arr[j])
		{
			arr[k]=aux_arr[i++];	
		}
		else
		{
			arr[k]=aux_arr[j++];
		}
	}
}

void merge_sort(int *arr,int lo,int hi)
{
	if(lo>=hi)
		return;
	int mid=(hi+lo)/2;	
	merge_sort(arr,lo,mid);
	merge_sort(arr,mid+1,hi);
	merge(arr,lo,mid,hi);
}

void quick_sort(int* arr,int lo,int hi)
{
	if(lo>=hi)
		return;
	int index=part(arr,lo,hi);
	quick_sort(arr,lo,index);
	quick_sort(arr,index+1,hi);
}

int main(int argc,char** argv)
{
	int arr[]={5,4,3,2,1,100,60};
	int count=sizeof(arr)/sizeof(int);
	printf("count:%d\n",count);
	quick_sort(arr,0,count-1);
	printf("arr:\n");
	int i;
	for(i=0;i<count;++i)
	{
		printf("%d,",arr[i]);
	}
	return 0;
}

