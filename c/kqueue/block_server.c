#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in listen_addr;
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(8888);
	listen_addr.sin_addr.s_addr = INADDR_ANY;

	socklen_t len = sizeof(listen_addr);

	if(bind(fd,(struct sockaddr*)&listen_addr,len)!=0)
	{
		perror("bind");
		return 1;
	}

	if(listen(fd,1)!=0)
	{
		perror("listen");
		return 1;
	}

	int i = 0;
	for(;;)
	{
		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		int client_fd;
		client_fd=accept(fd,(struct sockaddr*)&client_addr,&client_len);
		if(client_fd==-1)
		{
			perror("accept");
			return 1;
		}

		printf("Accepted:%d\n",++i);
	}
	return 0;
}
