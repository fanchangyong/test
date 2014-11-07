#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

// ps -ef|grep bash|nl
//

#define MAX_ARGS 10

struct cmd_t
{
	char* path;
	char* args[MAX_ARGS];
	int redirect_stdout;
	int redirect_stdin;
};

struct cmd_t cmds[]=
{
	//{"/bin/ls","ls","-l","/",NULL},
	{"/bin/ps","ps",NULL},
	{"/usr/bin/nl","nl",NULL}
};

int main()
{
	int len=sizeof(cmds)/sizeof(struct cmd_t);
	int i;

	int fds[len][2];
	//int *fds=malloc(sizeof(int)*(fdlen));
	// create pipes
	fds[0][0]=STDIN_FILENO;
	fds[len-1][1]=STDOUT_FILENO;

	for(i=1;i<len;++i)
	{
		int fd[2];
		pipe(fd);
		fds[i-1][1]=fd[1];
		fds[i][0]=fd[0];
	}

	for(i=0;i<len;++i)
	{
		struct cmd_t cmd=cmds[i];

		pid_t pid=fork();
		if(pid<0)
		{
			perror("fork");
		}
		else if(pid==0) // child
		{
			// dup read fd
				if(fds[i][0]!=STDIN_FILENO)
				{
					dup2(fds[i][0],STDIN_FILENO);
				}
			// dup write rd
				if(fds[i][1]!=STDOUT_FILENO)
				{
					dup2(fds[i][1],STDOUT_FILENO);
				}
			// close unused fds
			int j;
			for(j=0;j<len;++j)
			{
				if(fds[j][0]!=STDIN_FILENO)
				{
					close(fds[j][0]);
				}
				if(fds[j][1]!=STDOUT_FILENO)
				{
					close(fds[j][1]);
				}
			}
			printf("exec:%s\n",cmd.path);
			fflush(stdout);
			execv(cmd.path,cmd.args);
			perror("execv");
		}
		else // parent
		{
		}
	}

	// close all
	int j;
	for(j=0;j<len;++j)
	{
		if(fds[j][0]!=STDIN_FILENO)
		{
			close(fds[j][0]);
		}
		if(fds[j][1]!=STDOUT_FILENO)
		{
			close(fds[j][1]);
		}
	}

	// parent
	for(i=0;i<len;++i)
	{
		int stat;
		wait(&stat);
	}
}
