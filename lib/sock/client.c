#include "sock_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("Usage:./test <hostname> <port>\n");
		return 1;
	}
	char* name=argv[1];
	struct hostent* hent=gethostbyname(name);
	if(hent==NULL)
	{
		printf("gethostname error\n");
		return 1;
	}
	
	unsigned short port=(unsigned short)atoi(argv[2]);
	struct in_addr *addr=(struct in_addr*)hent->h_addr;
	char* straddr=inet_ntoa(*addr);

	int sock;
	if((sock=start_tcp_client(straddr,port))==-1)
	{
		perror("start client error");
		return -1;
	}
	printf("peer addr:%s:%hd\n",get_peer_addr(sock),get_peer_port(sock));
	printf("sockaddr:%s:%hu\n",get_sock_addr(sock),get_sock_port(sock));
	return 0;
}
