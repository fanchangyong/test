/*
 * 测试SO_LINGER的行为
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

void do_server()
{
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd==-1)
		err("socket");

	int reuseaddr = 1;
	socklen_t reuseaddrlen = sizeof(reuseaddr);
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,
				reuseaddrlen)==-1)
		err("setsockopt");

	struct linger l;
	l.l_onoff = 1;
	l.l_linger = 0;
	if(setsockopt(listenfd,SOL_SOCKET,SO_LINGER,&l,sizeof(l))==-1)
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

	char buf[102400];
	int n = write(clientfd,buf,sizeof(buf));
	printf("write n:%d,closing\n",n);
	n = close(clientfd);
	printf("close: %d\n",n);
}

void do_client()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
		err("socket");

	int rcvbuf = 1;
	setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&rcvbuf,sizeof(rcvbuf));

	socklen_t rcvbuflen;
	getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&rcvbuf,&rcvbuflen);
	printf("RCVBUF: %d\n",rcvbuf);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton("127.0.0.1",&addr.sin_addr);

	socklen_t len = sizeof(addr);

	if(connect(fd,(struct sockaddr*)&addr,len)==-1)
		err("connect");

	printf("client sleeping\n");
	sleep(10);
}

int main(int argc,char** argv)
{
	pid_t pid;
	if((pid=fork())==-1)
		err("fork");
	else if(pid==0) // child
	{
		do_server();
	}
	else // parent
	{
		sleep(1);
		do_client();
	}
	return 0;
}

