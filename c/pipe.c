#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

// ps -ef|grep bash|nl

int main()
{
	int fda[2];
	int fdb[2];
	pipe(fda);
	pipe(fdb);

	pid_t pid1,pid2,pid3;

	if((pid1=fork())==0)
	{
		// ps -ef
		// for output
		close(fda[0]);
		dup2(fda[1],STDOUT_FILENO);

		char* args[]={"ls","/",NULL};
		char cmd[]="/bin/ls";
		execv(cmd,args);
		perror("execv1");
	}

	if((pid2=fork())==0)
	{
		// grep bash
		// for input
		close(fda[1]);
		dup2(fda[0],STDIN_FILENO);

		// for output
		close(fdb[0]);
		dup2(fdb[1],STDOUT_FILENO);

		char* args[]={"grep","bash",NULL};
		char cmd[]="/usr/bin/grep";
		execv(cmd,args);
		perror("execv2");

	}

	if((pid3=fork())==0)
	{
		// nl
		// for input
		close(fdb[1]);
		dup2(fdb[0],STDIN_FILENO);

		char* args[]={"nl",NULL};
		char cmd[]="/usr/bin/nl";
		execv(cmd,args);
		perror("execv3");
	}

	int i;
	for(i=0;i<3;++i)
	{
		int stat;
		pid_t pid=wait(&stat);
		printf("pid:%d,stat:%d\n",pid,stat);
	}
}
