#include <stdio.h>

int arr[][3]={{1},{2,2}};
void print_arr(int (*arr)[3],int len);

const int max=3;
int iarr[]={[1 ... max]=1};

int main(int argc,char* argv[])
{
	printf("sizeof arr:%lu,sizeof arr0:%lu\n",sizeof(arr),sizeof(arr[0]));
	int len=sizeof(arr)/sizeof(arr[0]);
	print_arr(arr,len);
	return 0;
}

/*
 * When use multi-dimentionary array as a function parameter, 
 * we can use two forms:
 * 1.int arr[][3] (ordinary two-dimentionary array) or
 * 2.int (*arr)[3] (pointer to a one-dimentionary array which have 3 elements)
 * Note:the second-dimention length is required.
 */
void print_arr(int (*arr)[3],int len)
{
	printf("len of arr:%d\n",len);
	int i,j;
	// We traverse the array with array index
	for(i=0;i<len;i++)
	{
		for(j=0;j<3;j++)
			printf("arr[%d][%d]=%d\t",i,j,arr[i][j]);
		printf("\n");
	}
}
