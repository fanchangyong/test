#include <stdio.h>
#include "sock_util.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_PORT 8888


int main()
{
	int sock;
	int client_sock=start_tcp_server(LISTEN_PORT,&sock);
	if(client_sock==-1)
	{
		perror("start tcp server");
		return -1;
	}

	printf("client addr is:%s:%hu\n",get_peer_addr(client_sock),get_peer_port(client_sock));
	dup2(client_sock,STDIN_FILENO);
	// write something to client
	for(;;)
	{
		char buf[1024];
		ssize_t reat;
		if((reat=read(STDIN_FILENO,buf,1024))<0)
		{
			perror("read");
			break;
		}
		else if(reat==0)
		{
			printf("reading done\n");
			break;
		}
		else
		{
			printf("I have read:%s",buf);
			//write(STDOUT_FILENO,buf,reat);
		}
	}
	
	
	return 0;
}
