#include "inc.h"

char* pathname;
int fd;

void do_cmd();

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage: ./reader <pathname>\n");
		return 1;
	}
	pathname=argv[1];
	do_cmd();
	return 0;
}

void do_cmd()
{
	for(;;)
	{
		printf("%% ");
		int c=getchar();
		if(c=='o')
		{
			fd=open_file(pathname);
		}
		else if(c=='r')
		{
			read_file(fd);
		}
		else if(c=='e')
		{
			printf("exiting...\n");
			exit(0);
		}
		printf("\n");
	}
}

int open_file(char* pathname)
{
	int fd;
	if(-1==(fd=open(pathname,O_CREAT|O_RDWR,0640)))
	{
		perror("open error");
		exit(1);
	}
	return fd;
}

int read_file(int fd)
{
	char* buf=malloc(1024);
	for(;;)
	{
		int n=read(fd,buf,1024);
		if(-1==n)
		{
			perror("read error");
			exit(1);
		}
		else if(0==n)
		{
			printf("read end of file\n");
			break;
		}
		else
		{
			printf("read buf,n:%d:%s\n",n,buf);
		}
	}
	return 0;
}

