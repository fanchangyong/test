#include <stdio.h>
#include <stdlib.h>

/*
 * More efficient way
 *
 * */
int fib(int n)
{
	int arr[n+1];
	arr[0]=0;
	arr[1]=1;
	if(n<2)
		return n;
	int i;
	for(i=2;i<=n;++i)
		arr[i]=arr[i-1]+arr[i-2];
	for(i=0;i<=n;++i)
		printf("%d,",arr[i]);
	printf("\n");
	return arr[n];
}

/*
 * Space Efficient Way
 * */

int fib2(int n)
{
	int a=0;
	int b=1;
	int c;
	int i;
	for(i=2;i<=n;++i)
	{
		c=a+b;
		a=b;
		b=c;
	}
	return c;
}

/*
 * The slow way
 * */

int fibth(int n)
{
	if(n==0)
		return 0;
	if(n==1)
		return 1;
	return fibth(n-1)+fibth(n-2);
}

int main()
{
	int n=fib2(11);
	printf("%d\n",n);
}
