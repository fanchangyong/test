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
		char buf[]="process 111 saying";
		write(fda[1],buf,sizeof(buf)+1);
		exit(0);
	}

	if((pid2=fork())==0)
	{
		// grep bash
		// for input
		close(fda[1]);
		char buf[1024];
		read(fda[0],buf,sizeof(buf));
		printf("read from pipe in process 2,buf:%s\n",buf);

		// for output
		close(fdb[0]);
		char writebuf[]="from second process";
		write(fdb[1],writebuf,sizeof(writebuf)+1);
		exit(0);
	}

	if((pid3=fork())==0)
	{
		// nl
		// for input
		close(fdb[1]);
		char buf[1024];
		read(fdb[0],buf,sizeof(buf));
		printf("read from pipe in process 3 ,%s\n",buf);
		exit(0);

	}

	int stat;
	pid_t pid=wait(&stat);
	printf("pid:%d,stat:%d\n",pid,stat);
}
