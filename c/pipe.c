#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

// ps -ef|grep bash|nl

void handler(int sig)
{
	printf("sig:%d\n",sig);
}

int main()
{
	int fd[2];
	if(pipe(fd)<0)
	{
		perror("pipe");
		return 1;
	}
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork");
		return 1;
	}
	else if(pid==0)
	{
		// child
		close(fd[0]);
		close(fd[1]);
	}
	else if(pid>0)
	{
		signal(SIGPIPE,handler);
		close(fd[0]);
		char buf[]="hello";
		if(-1==write(fd[1],buf,sizeof(buf)))
		{
			perror("write");
		}
		printf("press any key...");
		getchar();
	}
	return 0;
}
