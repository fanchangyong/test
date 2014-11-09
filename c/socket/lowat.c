/*
 * TCP lowater
 *
 * Client send to server 1 byte per second,
 * on server,specify different recv lowwater
 * values to see the behavior of read syscall.
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

const int PORT = 8888;

void err(char* str)
{
	perror(str);
	exit(1);
}

void do_server(int lowat)
{
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd==-1)
		err("socket");

	int reuseaddr = 1;
	socklen_t reuseaddrlen = sizeof(reuseaddr);
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,
				reuseaddrlen)==-1)
		err("setsockopt");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t len = sizeof(addr);

	if(bind(listenfd,(const struct sockaddr*)&addr,len)==-1)
		err("bind");

	if(listen(listenfd,5)==-1)
		err("listen");

	printf("Server listening...\n");

	int clientfd = -1;
	if((clientfd=accept(listenfd,NULL,NULL))==-1)
		err("accept");

	int optval = lowat;
	int optlen = sizeof(optval);
	if(setsockopt(clientfd,SOL_SOCKET,SO_RCVLOWAT,&optval,optlen)==-1)
		err("setsockopt");

	for(;;)
	{
		char buf[1024];
		int n = read(clientfd,buf,sizeof(buf));
		if(n<0)
			err("read");
		else if(n==0)
		{
			exit(0);
		}
		else
		{
			printf("read :%d\n",n);
		}
	}
}

void do_client()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
		err("socket");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton("127.0.0.1",&addr.sin_addr);

	socklen_t len = sizeof(addr);

	if(connect(fd,(struct sockaddr*)&addr,len)==-1)
		err("connect");

	int i;
	for(i=0;i<10;i++)
	{
		char buf[1];
		int n = write(fd,buf,sizeof(buf));
		printf("writen:%d\n",n);
		sleep(1);
	}
}

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage: ./a.out <lowater>\n");
		return 1;
	}

	int lowat = atoi(argv[1]);

	pid_t pid;
	if((pid=fork())==-1)
		err("fork");
	else if(pid==0) // child
	{
		do_server(lowat);
	}
	else // parent
	{
		sleep(1);
		do_client();
	}
	return 0;
}

