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
		int fd=open("/dev/stdin",O_RDONLY);
		if(fd==-1)
		{
			perror("open");
			return 1;
		}
		printf("fd:%d\n",fd);
		char buf[1024];
		int ret=read(fd,buf,1024);
		printf("buf:%s\n",buf);
		if(ret==-1)
			printf("read:%d,errno:%d,err:%s\n",ret,errno,strerror(errno));
	}
	else
	{
		//getchar();
		sleep(3);
	}
}
