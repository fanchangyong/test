/*
 * 测试系统函数调用与普通函数调用的性能差别
 */

#include <time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int sys()
{
	return open("./non_exist",O_RDONLY);
}

int foo()
{
	return 0;
}

int function()
{
	return foo();
}

int bench_sys(int num)
{
	printf("Running syscall benchmark for %d numbers.\n",num);
	int i;
	int t1=time(NULL);
	for(i=0;i<num;i++)
	{
		sys();
	}
	int t2 = time(NULL);
	return t2-t1;
}

int bench_function(int num)
{
	printf("Runnint function benchmark for %d numbers.\n",num);
	int i;
	int t1=time(NULL);
	for(i=0;i<num;i++)
	{
		function();
	}
	int t2 = time(NULL);
	return t2-t1;
}

int main(int argc,char** argv)
{
	int num = 10000000;
	if(argc>=2)
	{
		num = atoi(argv[1]);
	}

	int t1 = bench_sys(num);
	int t2 = bench_function(num);
	printf("Syscal used:%d seconds,function used:%d seconds.\n",t1,t2);

	return 0;
}
