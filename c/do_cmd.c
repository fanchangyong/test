#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	char buf[1024];
	while(1)
	{
		printf("%% ");
		if(fgets(buf,1024,stdin)==NULL)
			break;
		buf[strlen(buf)-1]=NULL;
		do_cmd(buf);
	}
	printf("```break from while\n");
}

int do_cmd(char* cmd_str)
{
	pid_t p=fork();
	if(p==-1)
	{
		printf("fork error,no:%d\n",errno);
	}
	else if(p==0)
	{
		int ret=execlp(cmd_str,cmd_str,NULL);
		if(ret==-1)
		{
			perror("An error occured:");
			//char* strerr=strerror(errno);
			//printf("```ret :%d,error:%s\n",ret,strerr);
		}
	}
	else
	{
		int status;
		waitpid(p,&status,0);
	}
}
