#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage: ./a.out addr [port]\n");
		return -1;
	}

	char* addr = argv[1];

	unsigned short port = 80;
	if(argc>2)
	{
		port = atoi(argv[2]);
	}

	struct sockaddr_in iaddr;
	iaddr.sin_family = AF_INET;
	iaddr.sin_port = htons(port);
	inet_aton(addr,&iaddr.sin_addr);

	socklen_t len = sizeof(iaddr);

	char host[1024];
	socklen_t hostlen = sizeof(host);

	char serv[1024];
	socklen_t servlen = sizeof(serv);

	int ret = getnameinfo((struct sockaddr*)&iaddr,
			len,host,hostlen,serv,servlen,0);
	
	if(ret==0)
	{
		printf("Host:%s,Serv:%s\n",host,serv);
	}
	else
	{
		perror("getnameinfo");
	}

	return 0;
}
