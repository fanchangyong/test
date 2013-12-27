#include "sock_util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**********************************
 * for server
 *********************************/

int create_tcp_sock()
{
	return socket(AF_INET,SOCK_STREAM,0);
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
	struct sockaddr_in *tmp_addr=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	socklen_t *tmp_len=malloc(sizeof(socklen_t));
	if((client_sock=accept(sock,(struct sockaddr*)tmp_addr,tmp_len))==-1)
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
	if(listen(sock,5)==-1)
	{
		return -1;
	}

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

int connect_to(int sock,char* str_addr,unsigned short port)
{
	struct sockaddr_in addr;
	bzero(&addr,sizeof(struct sockaddr_in));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(str_addr);
	addr.sin_port=htons(port);
	socklen_t len=sizeof(struct sockaddr_in);
	return connect(sock,(struct sockaddr*)&addr,len);
}


int start_tcp_client(char* str_addr,unsigned short port)
{
	int sock=create_tcp_sock();
	if(-1==connect_to(sock,str_addr,port))
	{
		return -1;
	}
	return sock;
}


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
	socklen_t addr_len=sizeof(struct sockaddr_in);
	if(-1==getsockname(sock,(struct sockaddr*)&client_addr,&addr_len))
	{
		perror("getsockname error");
		return "";
	}

	return inet_ntoa(client_addr.sin_addr);
}

unsigned short get_sock_port(int sock)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len=sizeof(struct sockaddr_in);
	if(-1==getsockname(sock,(struct sockaddr*)&client_addr,&addr_len))
	{
		perror("getsockname port error");
		return -1;
	}

	return htons(client_addr.sin_port);
}

char* get_peer_addr(int sock)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len=sizeof(struct sockaddr_in);
	if(-1==getpeername(sock,(struct sockaddr*)&client_addr,&addr_len))
	{
		perror("getpeername error");
		return "";
	}

	return inet_ntoa(client_addr.sin_addr);
}

unsigned short get_peer_port(int sock)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len=sizeof(struct sockaddr_in);
	if(-1==getpeername(sock,(struct sockaddr*)&client_addr,&addr_len))
	{
		perror("getpeername port error");
		return -1;
	}

	return htons(client_addr.sin_port);
}
