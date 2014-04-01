#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

int main(int argc,char** argv)
{
	if(argc!=3)
	{
		printf("Usage: ./a.out <ipaddress> <port>\n");
		return 1;
	}
	// create socket
	int sock = socket(PF_INET,SOCK_STREAM,0);

	// construct address
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	if(inet_aton(argv[1],&addr.sin_addr)!=1)
	{
		perror("inet_aton");
		return 1;
	}

	int connect_result = connect(sock,(struct sockaddr*)&addr,sizeof(addr));
	printf("connect result:%d\n",connect_result);
	if(connect_result!=0)
	{
		perror("connect");
		getchar();
	}
	else
	{
		int len=1024*1024;
		char *buf=malloc(len);
		printf("buf:%p\n",buf);
		bzero(buf,len);
		printf("to write\n");
		int ret = write(sock,buf,len);
		printf("write result:%d\n",ret);
		if(-1==ret)
		{
			perror("send");
		}
		else
		{
			printf("send return:%d",ret);
		}
	}
	return 0;
}
