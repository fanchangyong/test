#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

void err(char* str)
{
	perror(str);
	exit(-1);
}

int main()
{
	char path[] = "./myfifo";
	mkfifo(path,O_RDWR);

	pid_t pid;
	if((pid=fork())<0)
	{
		err("fork");
	}
	else if(pid>0) // parent
	{
		int fd = open(path,O_RDWR);
		if(fd==-1)
		{
			err("open");
		}

		char buf[1024];
		int ret = read(fd,buf,sizeof(buf));
		printf("read return:%d\n",ret);
		printf("parent receive:%s\n",buf);
	}
	else // child
	{
		int fd = open(path,O_RDWR);
		if(fd==-1)
		{
			err("open");
		}

		char buf[]="Writing from child";
		int ret = write(fd,buf,sizeof(buf));
		printf("write return:%d\n",ret);
	}

}
