/*
 * 前3次,echo
 * 然后服务器再发3次,客户端只收不发
 *
 * 如果调用shutdown(fd,SHUT_WR)之后
 * 继续调用write,会产生SIGPIPE
 * 如果调用shutdown(fd,SHUT_RD)之后
 * 继续调用read,会返回EOF
 *
 */

#include <signal.h>
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

	int eof = 0;
	for(;;)
	{
		if(!eof)
		{
			char buf[1024];
			int n = read(clientfd,buf,sizeof(buf));
			if(n<0)
				err("read");
			else if(n==0)
			{
				// peer closed
				printf("EOF\n");
				eof = 1;
			}
			else
			{
				write(clientfd,buf,n);
			}
		}
		else
		{
			int i;
			for(i=0;i<3;i++)
			{
				char buf[1];
				buf[0]='s';
				write(clientfd,buf,sizeof(buf));
				sleep(1);
			}
			close(clientfd);
			break;
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

	// echo
	int i;
	for(i=0;i<3;i++)
	{
		char buf[1];
		buf[0]='a';
		write(fd,buf,sizeof(buf));
		read(fd,buf,sizeof(buf));
		printf("client: %c\n",buf[0]);
		sleep(1);
	}

	// won't write anymore
	shutdown(fd,SHUT_WR);
	printf("client shutdown\n");

	for(i=0;i<3;i++)
	{
		char buf[1];
		read(fd,buf,sizeof(buf));
		printf("client: %c\n",buf[0]);
	}
	printf("client :close\n");
	close(fd);
}

int main(int argc,char** argv)
{
	signal(SIGPIPE,SIG_IGN);
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

