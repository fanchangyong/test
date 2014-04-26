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

	fork();

	if(listen(fd,5)!=0)
	{
		perror("listen");
		return 1;
	}

	printf("listen ok,pid:%d\n",getpid());

	for(;;)
	{
		if(accept(fd,NULL,NULL)==-1)
		{
			perror("accept");
			return 1;
		}
		printf("accept ok,pid:%d\n",getpid());
	}


	return 0;
}
