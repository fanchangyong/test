/*
 * 客户端服务器只有一方调用close的情况
 *
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PORT 8888

void err(char* str)
{
	perror(str);
}

void sock_server()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1) err("socket");

	int optval = 1;
	socklen_t optlen = sizeof(optval);
	if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&optval,optlen)==-1)
		err("setsockopt");

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	socklen_t socklen = sizeof(struct sockaddr_in);
	if(bind(fd,(struct sockaddr*)&addr,socklen)==-1) err("bind");

	if(listen(fd,5)==-1) err("listen");

	int sock = -1;
	if((sock = accept(fd,NULL,NULL))==-1) err("accept");

	printf("Accepted a client,close it!\n");
	close(sock,SHUT_WR);
	printf("Server side closed\n");
}


void sock_client()
{
	sleep(1);
	printf("Starting client..\n");
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1) err("socket");

	struct sockaddr_in addr;
	inet_aton("127.0.0.1",&addr.sin_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	if(connect(fd,(struct sockaddr*)&addr,sizeof(addr))==-1)
		err("connect");

	char buf[1024];
	if(read(fd,buf,sizeof(buf))==0)
	{
		sleep(5);
		printf("Client side close\n");
		close(fd);
	}

}

int main(int argc,char** argv)
{
	pid_t pid;
	if((pid=fork())<0)
	{
		err("fork");
	}
	else if(pid==0) // child process,tcp server
	{
		sock_server();
	}
	else // parent
	{
		sock_client();
	}
	return 0;
}
