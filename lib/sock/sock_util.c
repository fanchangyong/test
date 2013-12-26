#include "sock_util.h"
#include <string.h>
#include <stdio.h>

/**********************************
 * for server
 *********************************/

int create_tcp_sock()
{
	return socket(PF_INET,SOCK_STREAM,0);
}

int bind_by_port(int sock,unsigned short port)
{
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=INADDR_ANY;
	socklen_t len=sizeof(struct sockaddr_in);
	return bind(sock,(struct sockaddr*)&addr,len);
}

int do_accept(int sock)
{
	struct sockaddr_in sockaddr;
	socklen_t len;
	int client_sock;
	struct sockaddr_in tmp_addr;
	socklen_t tmp_len;
	if((client_sock=accept(sock,(struct sockaddr*)&tmp_addr,&tmp_len))==-1)
	{
		printf("accept error\n");
		return -1;
	}
	else
	{
		return client_sock;
	}
}

int start_tcp_server(unsigned short port,int* server_sock)
{
	int sock=create_tcp_sock();
	printf("sock is:%d\n",sock);
	if(sock==-1)
	{
		return -1;
	}
	if(set_reuse_addr(sock)==-1)
	{
		return -1;
	}
	if(bind_by_port(sock,port)==-1)
	{
		return -1;
	}
	printf("bind socuccess\n");
	if(listen(sock,5)==-1)
	{
		return -1;
	}

	printf("listen success\n");
	int client_sock;
	if((client_sock=do_accept(sock))==-1)
	{
		return -1;
	}
	*server_sock=sock;
	return client_sock;
}

/**********************************
 * for client
 *********************************/




/**********************************
 * util
 *********************************/

int set_reuse_addr(int sock)
{
	int opt=1;
	return setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

char* get_sock_addr(int sock)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len;
	if(-1==getpeername(sock,(struct sockaddr*)&client_addr,&addr_len))
	{
		perror("getpeername error");
		return "";
	}

	return inet_ntoa(client_addr.sin_addr);
}

unsigned short get_sock_port(int sock)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len;
	if(-1==getpeername(sock,(struct sockaddr*)&client_addr,&addr_len))
	{
		perror("getpeername port error");
		return -1;
	}

	return client_addr.sin_port;
}
