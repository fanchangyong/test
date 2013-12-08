#include <stdio.h>

int fac(int n)
{
	printf("==>Entering fac,n is:%d\n",n);
	if(n==1)
	{
		printf("######Returnning 1\n");
		return n;
	}
	printf("^^^^^^^^Returnning %d*fac(%d)\n",n,n-1);
	int r= n*fac(n-1);
	printf("$$$$$$$$Returnning from fac(%d),r is:%d\n",n-1,r);
	return r;
}

int fib(int n)
{
	printf("Entering fib,n is:%d\n",n);
	if(n==0)
	{
		printf("n is 0,returnning 1\n");
		return 1;
	}
	if(n==1)
	{
		printf("n is 1,returnning 2\n");
		return 2;
	}
	printf("####Going to call fib-1(%d),n is:%d\n",n-1,n);
	int n1=fib(n-1);
	printf("$$$$$$Going to call fib-2(%d),n is:%d\n",n-2,n);
	int n2=fib(n-2);
	printf("!!!!!!Returning as %d,when n is:%d\n",n1+n2,n);
	return n1+n2;
}

void pr_fib(int n)
{
	if(n==0)
	{
		printf("1 ");
		return;
	}
	if(n==1)
	{
		printf("2 ");
		return;
	}
	pr_fib(n-1);
	pr_fib(n-2);
}


int main()
{
	pr_fib(3);
}
