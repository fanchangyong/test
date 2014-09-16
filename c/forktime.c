#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void do_something()
{
	printf("I am child!\n");
	exit(0);
}

int main(int argc,char** argv)
{
	int count;

	int c;
	for(;;)
	{
		c = getopt(argc,argv,"c:");
		if(c==-1)
			break;

		switch(c)
		{
			case 'c':
				count = atoi(optarg);
				break;
		}
	}

	struct timeval t1;
	if(-1==gettimeofday(&t1,NULL))
	{
		perror("gettimeofday");
		return -1;
	}

	for(int i = 0;i<count;i++)
	{
		pid_t p;
		if((p=fork())==0)
		{
			do_something();
		}
		if(p<0)
		{
			printf("i:%d\n",i);
			perror("fork");
			break;
		}
	}

	struct timeval t2;
	if(-1==gettimeofday(&t2,NULL))
	{
		perror("gettimeofday");
		return -1;
	}

	long tt1 = t1.tv_sec*1000*1000+t1.tv_usec;
	long tt2 = t2.tv_sec*1000*1000+t2.tv_usec;

	printf("fork %d times,time used:%ld ms\n",count,(tt2-tt1)/1000);
	return 0;
}
