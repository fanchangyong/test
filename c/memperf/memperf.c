/*
 * 测试内存复制的性能
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage: ./a.out <len>\n");
		return -1;
	}

	time_t t1,t2;

	int len = atoi(argv[1]);
	int mb = len*1024*1024;
	t1=time(NULL);
	char* psrc = malloc(mb);
	if(psrc==0)
	{
		perror("malloc");
		return -1;
	}
	t2=time(NULL);
	printf("Allocated %d MB in %ld seconds\n",len,t2-t1);

	t1=time(NULL);
	char* pdst = malloc(mb);
	if(psrc==0)
	{
		perror("malloc");
		return -1;
	}
	t2=time(NULL);
	printf("Allocated %d MB in %ld seconds\n",len,t2-t1);

	const int count = 10;
	int i;
	long sumtime=0;
	for(i=0;i<count;i++)
	{
		t1=time(NULL);
		memcpy(pdst,psrc,mb);
		t2=time(NULL);
		sumtime += (t2-t1);
	}

	printf("sumtime:%ld,count:%d,average used:%ld\n",sumtime,count,sumtime/count);
	return 0;
}
