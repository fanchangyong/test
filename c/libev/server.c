#include <ev.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>


void read_cb(struct ev_loop *loop,ev_io* w,int revents)
{
	int fd = w->fd;
	char buf[1024];
	int n = read(fd,buf,sizeof(buf));
	if(n==0)
	{
		printf("EOF\n");
		ev_io_stop(loop,w);
	}
	else if(n<0)
	{
		perror("read error\n");
		exit(1);
	}
	else
	{
		printf("%s",buf);
	}
}

void accept_cb(struct ev_loop *loop,ev_io* w,int revents)
{
	int fd = w->fd;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int client_sock = accept(fd,(struct sockaddr*)&addr,&len);
	if(client_sock==-1)
	{
		perror("accept");
		exit(1);
	}
	printf("[%d] Client:%s:%d\n",
			getpid(),
			inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

	struct ev_io *read_watcher = malloc(sizeof(struct ev_io));
	ev_init(read_watcher,read_cb);
	ev_io_set(read_watcher,client_sock,EV_READ);
	ev_io_start(loop,read_watcher);
}

int main(int argc,char** argv)
{

	int lsock = socket(AF_INET,SOCK_STREAM,0);
	if(lsock==-1)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8888);

	socklen_t len = sizeof(addr);

	if(bind(lsock,(struct sockaddr*)&addr,len)==-1)
	{
		perror("bind");
		return 1;
	}

	if(listen(lsock,5)==-1)
	{
		perror("listen");
	}

	// Create event loop
	struct ev_loop *loop = ev_default_loop(0);
	if(!loop)
	{
		printf("cannot initiate libev\n");
		return 1;
	}

	int i;
	for(i=0;i<4;i++)
	{
		ev_io server_watcher;
		ev_init(&server_watcher,accept_cb);
		ev_io_set(&server_watcher,lsock,EV_READ);
		ev_io_start(loop,&server_watcher);

		printf("Rnning event loop...\n");
		ev_run(loop,0);
	}

	return 0;
}
