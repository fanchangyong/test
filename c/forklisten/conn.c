#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char** argv)
{
	while(1)
	{
		int fd = socket(PF_INET,SOCK_STREAM,0);
		if(fd==-1)
		{
			perror("socket error\n");
			return 1;
		}
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(8888);
		if(connect(fd,(struct sockaddr*)&addr,sizeof(addr))!=0)
		{
			perror("connect");
			return 1;
		}
		printf("ok\n");
		close(fd);
		sleep(1);
	}

	return 0;
}
