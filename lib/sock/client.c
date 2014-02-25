#include "sock_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

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
	char buf[1024];
	int i;
	for(i=0;i<100000;++i)
	{
		write(sock,buf,1024);
		printf("writing 1024 bytes,i:%d\n",i);
	}
	return 0;
}
