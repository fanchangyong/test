#include "inc.h"
#include <fcntl.h>

#define BUFF_SIZE 10

int main(int argc,char** argv)
{
	const char path1[]="/bin/ps";
	char* args1[]={"ps","-ef",NULL};
	const char path2[]="/usr/bin/grep";
	char* args2[]={"grep","bash",NULL};

	int fd[2];
	pipe(fd);
	printf("fd0:%d,fd1:%d\n",fd[0],fd[1]);
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid==0)
	{
		// child
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		execv(path1,args1);
	}
	else
	{
		// parent
		dup2(fd[0],STDIN_FILENO);
		close(fd[1]);
		execv(path2,args2);
	}

}
