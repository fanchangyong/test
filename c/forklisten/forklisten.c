#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	int fd = socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket error");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8888);
	if(bind(fd,(struct sockaddr*)&addr,sizeof(addr))!=0)
	{
		perror("bind");
		return 1;
	}


	int i;
	for(i=0;i<3;i++)
	{
		fork();
	}
	if(listen(fd,5)!=0)
	{
		perror("listen");
		return 1;
	}

	printf("listen ok,pid:%d\n",getpid());

	for(;;)
	{
		int cli_fd = 0;
		if((cli_fd=accept(fd,NULL,NULL))==-1)
		{
			perror("accept");
			return 1;
		}
		
		printf("accept ok,pid:%d\n",getpid());

		close(cli_fd);
	}


	return 0;
}
