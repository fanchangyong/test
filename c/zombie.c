/*
 * Generate a zombie process
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void err(char* str)
{
	perror(str);
	exit(1);
}

int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		err("fork");
	}
	else if(pid==0) // child
	{
		printf("child exit\n");
		exit(0);
	}
	else // parent
	{
		sleep(60);
		printf("parent exit\n");
	}
	return 0;
}
