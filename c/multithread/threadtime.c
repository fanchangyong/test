#include <stdio.h>
#include <getopt.h>
#include <pthread.h>
#include <stdlib.h>

void* entry(void* p)
{
	sleep(10);
	return NULL;
}

int main(int argc,char** argv)
{
	int count = 0;
	
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

	int i;
	time_t t1 = time(NULL);
	for(i=0;i<count;i++)
	{
		pthread_t p;
		if(pthread_create(&p,NULL,entry,NULL)!=0)
		{
			printf("i:%d\n",i);
			perror("pthread_create");
			break;
		}
	}
	time_t t2 = time(NULL);
	printf("Created %d threads,time used:%ld\n",i,t2-t1);
	sleep(10);
	return 0;
}
