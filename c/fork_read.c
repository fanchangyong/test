#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

extern int errno;
 
int main()
{
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid==0)
	{
		printf("read in child\n");
		int ret=getchar();
		printf("ret in child:%d\n",ret);
	}
	else
	{
		sleep(2);
		printf("read in parent\n");
		int ret=getchar();
		printf("ret in parent:%d\n",ret);
	}
}
