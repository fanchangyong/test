#include "inc.h"


int main(int argc,char** argv)
{
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		// first child
		sleep(4);
		abort();
		pid_t pid2;
		pid2=fork();
		if(pid2==0)
		{
			pid_t pid3=fork();
			if(pid3==0)
			{
				pid_t pid4=fork();
				if(pid4==0)
				{
					sleep(6);
					kill(getpid(),SIGKILL);
				}
				sleep(8);
				exit(0);
			}
			else if(pid3>0)
			{
				if(-1==execl("/bin/dd","/bin/dd",NULL))
				{
					perror("execl");
					exit(3);
				}
			}
		}
	}
	else if(pid>0)
	{
		sleep(2);
		exit(2);
	}

	return 0;
}
