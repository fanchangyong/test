#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int i;
	for(i=0;i<1000;i++)
	{
		pid_t pid;
		if((pid=fork())<0)
		{
			printf("i:%d\n",i);
			perror("fork");
			exit(1);
		}
		else if(pid==0) // child
		{
			execve("./worker",NULL,NULL);
			perror("execve");
			exit(1);
		}
	}
	return 0;
}
