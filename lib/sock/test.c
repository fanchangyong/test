#include <stdio.h>
#include "sock_util.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_PORT 8888

void print_byte(void* ptr,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%hhd\t",((char*)ptr)[i]);
	printf("\n");
}

void print_char(char* str,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%c,",str[i]);
	printf("\n");
}

void num_to_str(int n)
{
	char str[1024];
	bzero(str,1024);
	int i=0;
	int tmp=0;
	while(n>0)
	{
		tmp=n % 10;
		str[i]=tmp+'0';
		n=n/10;
		++i;
	}
	printf("str:%s\n",str);
}

int main()
{
	int sock;
	int client_sock=start_tcp_server(LISTEN_PORT,&sock);
	if(client_sock==-1)
	{
		perror("start tcp server");
		return -1;
	}

	printf("sock:%d,client sock:%d\n",sock,client_sock);
	char* str_addr=get_sock_addr(client_sock);
	unsigned short port=get_sock_port(client_sock);
	printf("client addr:%s:%hu\n",str_addr,port);

	// write something to client
	char buf[1024];
	bzero(buf,1024);
	strcpy(buf,"hello");
	write(client_sock,buf,strlen(buf)+1);
	
	getchar();
	
	return 0;
}
