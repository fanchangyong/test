#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

extern int errno;

int globvar=6;

int main()
{
	int var=0;
	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid==0)
	{
		globvar++;
		var++;
	}
	else
	{
		globvar++;
		var++;
		sleep(2);
	}
	printf("pid=%d,var=%d,global=%d\n",getpid(),var,globvar);
	return 0;
}

