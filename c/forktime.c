#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>

void do_something()
{
	sleep(10);
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

	time_t t1 = time(NULL);
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
	time_t t2 = time(NULL);

	printf("fork %d times,time used:%ld\n",count,t2-t1);
	return 0;
}
