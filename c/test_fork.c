#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	pid_t pid=fork();
	//printf("my pid is:%d,my ppid is:%d\n",getpid(),getppid());
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid==0)
	{
		/* Child */
		FILE* fp=fopen("/dev/stdin","r");
		char buf[1024];
		size_t ret=fread(buf,1024,1,fp);
		if(feof(fp))
		{
			printf("feof\n");
		}
		else if(ferror(fp))
		{
			perror("fread\n");
		}
		printf("ret=%lu,buf:%s\n",ret,buf);
	}
	else
	{
		printf("pid is:%u,father process quit\n",pid);
		int stat;
		waitpid(pid,&stat,0);
	}
	return 0;
}
