#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main()
{
	int fd = socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket");
		return -1;
	}

	int enable = 1;
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&enable,sizeof(enable));

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = INADDR_ANY;
	socklen_t len = sizeof(saddr);
	if(bind(fd,(struct sockaddr*)&saddr,len)==-1)
	{
		perror("bind");
		return -1;
	}

	if(listen(fd,5)==-1)
	{
		perror("listen");
		return -1;
	}

	for(;;)
	{
		struct sockaddr_in caddr;
		socklen_t len = sizeof(caddr);
		int clt_fd ;
		if((clt_fd=accept(fd,(struct sockaddr*)&caddr,&len))==-1)
		{
			continue;
		}
		int flags = fcntl(clt_fd,F_GETFL);
		if(flags & O_NONBLOCK)
		{
			printf("nonblock\n");
		}
		else
		{
			printf("block\n");
		}
	}

	return 0;
}
