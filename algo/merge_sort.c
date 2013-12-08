#include "inc.h"

void merge(int*,int,int,int);
void pr(int* arr,int len);

void partition(int* arr,int l,int r)
{
//printf("#####partition,l:%d,r:%d\n",l,r);
	if(l<r)
	{
		int m=(r+l)/2;
		partition(arr,l,m);
		partition(arr,m+1,r);
		merge(arr,l,m,r);
	}
}

void merge(int* arr,int l,int m,int r)
{
	int lenl=m-l+1;
	int lenr=r-m;
//printf("```merge,l:%d,m:%d,r:%d,lenl:%d,lenr:%d\n",l,m,r,lenl,lenr);
	int* larr=malloc(sizeof(int)*lenl);
	int* rarr=malloc(sizeof(int)*lenr);
	int i=l;
	int j=0;
	for(;j<lenl;++j,++i)
		larr[j]=arr[i];

	i=m+1;
	j=0;
	for(;j<lenr;++j,++i)
		rarr[j]=arr[i];

	i=0;
	int pl=0,pr=0;
	int pa=l;
	for(;;)
	{
		if(larr[pl]<rarr[pr])
		{
			arr[pa++]=larr[pl++];
		}
		else if(rarr[pr]<larr[pl])
		{
			arr[pa++]=rarr[pr++];
		}
		else
		{
			arr[pa++]=larr[pl++];
		}	
		if(pl==lenl)
		{
			while(pr<lenr)
				arr[pa++]=rarr[pr++];

			break;
		}
		if(pr==lenr)
		{
			while(pl<lenl)
				arr[pa++]=larr[pl++];
			break;
		}
	}
	free(larr);
	free(rarr);
}

void merge_sort(int* arr,int len)
{
	partition(arr,0,len-1);
}

int main(int argc,char** argv)
{
	srand(time(NULL));
#define LEN 10
	int i;
	int arr[LEN];
	for(i=0;i<LEN;++i)
	{
		int r=rand()%10000;
		arr[i]=r;
	}
	int len=sizeof(arr)/sizeof(int);
	printf("##### Before sorting:");
	pr(arr,len);
	merge_sort(arr,len);
	printf("\n\n\n");
	printf("##### After All:");
	pr(arr,len);
	return 0;
}

void pr(int* arr,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%d,",arr[i]);

	printf("\n");
}
