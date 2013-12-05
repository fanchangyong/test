#include "inc.h"

#define BUFF_SIZE 10

int main(int argc,char** argv)
{
	int fd=open("./test.txt",O_RDONLY|O_CREAT);
	int fd2=open("./test.txt",O_RDONLY);
	int fd3=open("./test.txt",O_RDONLY);
	printf("fd:%d,fd2:%d,fd3:%d\n",fd,fd2,fd3);
	if(fd==-1)
		perror("open file error");

	if(fd2==-1)
		perror("open file2 error");

	if(fd3==-1)
		perror("open file3 error");

	pid_t p=fork();
	if(p==-1)
	{
		perror("fork error");
	}
	else if(p==0)
		// in child
	{
		char *buf="child\n";
		int i;
		for(i=0;i<1000;i++)
			write(fd,buf,strlen(buf));
	}
	else
	{
		// in parent
		char *buf="parent\n";
		int i;
		for(i=0;i<1000;i++)
			write(fd,buf,strlen(buf));
	}
}
