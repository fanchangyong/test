#include "inc.h"

char* pathname;
int fd;
void do_cmd();

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage: ./writer <pathname>\n");
		return 1;
	}
	pathname = argv[1];
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
		else if(c=='w')
		{
			write_file(fd);
		}
		else if(c=='d')
		{
			unlink(pathname);
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

int write_file(int fd)
{
	int i;
	for(i=0;i<10;i++)
	{
		char buf[128];
		if(snprintf(buf,sizeof(buf),"I am writing the"
					"%d th element\n",i)<0)
		{
			perror("snprintf error");
			exit(1);
		}
		if(-1==write(fd,buf,strlen(buf)))
		{
			perror("write error");
			exit(1);
		}
		//sleep(1);
	}
	return 0;
}

