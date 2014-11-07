#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int connections = 10000;
char* addr;
unsigned short port;
int proc_num = 4;

int conn()
{
	int i;
	for(i=0;i<connections;i++)
	{
		int sock = socket(PF_INET,SOCK_STREAM,0);
		if(sock==-1)
		{
			perror("socket");
			return 1;
		}
		int flags = fcntl(sock,F_GETFL);
		if(fcntl(sock,F_SETFL,flags|O_NONBLOCK)==-1)
		{
			perror("fcntl");
			return 1;
		}

		struct sockaddr_in remote_addr;
		remote_addr.sin_family = AF_INET;
		remote_addr.sin_addr.s_addr = inet_addr(addr);
		remote_addr.sin_port = htons(port);

		socklen_t addrlen = sizeof(struct sockaddr_in);

		if(connect(sock,(struct sockaddr*)&remote_addr,addrlen)==-1)
		{
			if(errno!=EINPROGRESS) perror("connect");
		}
	}
	printf("Connect done\n");
	return 0;
}

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("Usage: ./a.out addr port\n");
		return 1;
	}
	addr = argv[1];
	port = atoi(argv[2]);
	

	conn();

	printf("press any key...\n");
	getchar();
	return 0;
}
