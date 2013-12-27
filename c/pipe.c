#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int fd=open("./pipedata",O_RDWR|O_CREAT);
	if(fd==-1)
	{
		perror("open");
		return 1;
	}
	int fds[2]={fd,STDOUT_FILENO};
	if(-1==pipe(fds))
	{
		perror("pipe");
		return 1;
	}
	int newfd=dup2(fd,STDOUT_FILENO);
	char buf[]="Write from pipe\n";
	write(newfd,buf,strlen(buf)+1);

	return 0;
}
