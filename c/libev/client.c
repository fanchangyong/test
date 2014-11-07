#include <ev.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

// 连接数
int connections = 1000;

void conn_cb(struct ev_loop* loop,ev_io *w,int revents)
{
	int fd = w->fd;
	printf("connected:%d\n",fd);
}


int do_connect(struct ev_loop* loop)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1)
	{
		perror("socket");
		return 1;
	}

	int flags = 0;
	if((flags=fcntl(sock,F_GETFD))==-1)
	{
		perror("fcntl");
		exit(1);
	}

	if((flags=fcntl(sock,F_SETFD,flags | O_NONBLOCK))==-1)
	{
		perror("fcntl");
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	inet_aton("127.0.0.1",&addr.sin_addr);
	addr.sin_port = htons(8888);
	socklen_t len = sizeof(addr);

	ev_io *conn_watcher = malloc(sizeof(ev_io));
	ev_init(conn_watcher,conn_cb);
	ev_io_set(conn_watcher,sock,EV_WRITE);
	ev_io_start(loop,conn_watcher);

	if(connect(sock,(struct sockaddr*)&addr,len)==-1
			&& errno != EAGAIN)
	{
		perror("connect");
		exit(1);
	}
	return 0;
}

void* thread_entry(void* p)
{
	struct ev_loop* loop = (struct ev_loop*)p;
	int i;
	for(i=0;i<connections;i++)
	{
		do_connect(loop);
	}
	return NULL;
}

int main(int argc,char** argv)
{
	int i;
	for(i=0;i<4;i++)
	{
		struct ev_loop* loop = ev_default_loop(0);
		if(!loop)
		{
			printf("cannot initiate libev\n");
			return 1;
		}
		pthread_t t;
		pthread_create(&t,NULL,thread_entry,loop);
	}

	ev_run(loop,0);

	return 0;
}
