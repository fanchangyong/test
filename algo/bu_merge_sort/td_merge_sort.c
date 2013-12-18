#include <stdio.h>
#include <stdlib.h>

#include "merge.h"

// 2013-12-12 17:09
// Top-Down Mergesort Implementation
//
void top_down_merge_sort(int* arr,int lo,int hi)
{
	int mid=(hi+lo)/2;	
	if(lo>=hi)
		return;
	top_down_merge_sort(arr,lo,mid);
	top_down_merge_sort(arr,mid+1,hi);
	merge(arr,lo,mid,hi);
}

int min(int a,int b)
{
	if(a<=b)
		return a;
	return b;
}

// Bottom Up Mergesort Implementation
void bottom_up_merge_sort(int* arr,int len)
{
	int i;
	int sz=1;
	for(;sz<len;sz+=sz)
	{
		printf("sz=%d\n",sz);
		int i;
		for(i=0;i<len-sz;i+=sz+sz)
		{
			int lo=i;
			int m=i+sz-1;
			int hi=min(i+sz+sz-1,len-1);
			printf("lo:%d,m:%d,hi:%d\n",lo,m,hi);
			merge(arr,lo,m,hi);
		}
	}
}

int main(int argc,char** argv)
{
#define LEN 100
	int arr[LEN];
	int i;
	for(i=0;i<LEN;++i)
		arr[i]=LEN-i;
	bottom_up_merge_sort(arr,LEN);
//	for(i=0;i<LEN-1;++i)
//		printf("%d,",arr[i]);

	printf("\n");
	return 0;
}
