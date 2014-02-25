#include "inc.h"
#include <fcntl.h>

#define BUFF_SIZE 10

int main(int argc,char** argv)
{
	const char path1[]="/bin/ls";
	char* args1[]={"ps","-ef",NULL};
	const char path2[]="/usr/bin/grep";
	char* args2[]={"grep","bash",NULL};
	const char path3[]="/usr/bin/nl";
	char* args3[]={"nl",NULL};

	int fd[2];
	if(-1==pipe(fd))
	{
		perror("pipe");
		return 1;
	}
	printf("fd0:%d,fd1:%d\n",fd[0],fd[1]);
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid==0)
	{
		// child
		if(-1==dup2(fd[1],STDOUT_FILENO))
		{
			perror("dup2");
		}
		close(fd[0]);
		if(-1==execv(path1,args1))
		{
			perror("execv1");
		}
	}
	else
	{
		// parent
		// fork again
		int fd2[2];
		if(-1==pipe(fd2))
		{
			perror("pipe");
		}
		printf("fd2[0]:%d,fd2[1]:%d\n",fd2[0],fd2[1]);
		pid_t pid2=fork();
		if(pid2<0)
		{
			perror("fork 2");
		}
		else if(pid2==0)
		{
			// child
			if(-1==dup2(fd[0],STDIN_FILENO))
			{
				perror("dup2");
			}
			close(fd[1]);

			if(-1==dup2(fd2[1],STDOUT_FILENO))
			{
				perror("dup2");
			}
			close(fd2[0]);
			//close(STDOUT_FILENO);

			if(-1==execv(path2,args2))
			{
				perror("execv2");
			}
		}
		else
		{
			if(-1==dup2(fd2[0],STDIN_FILENO))
			{
				perror("dup2");
			}
			close(fd2[1]);
			if(-1==execv(path3,args3))
			{
				perror("execv3");
			}
		}
	}

}
