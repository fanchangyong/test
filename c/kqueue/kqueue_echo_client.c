#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

void err(char* str)
{
	perror(str);
	exit(1);
}

void reg_write_fd(int kq,int fd)
{
	struct kevent ev;
	bzero(&ev,sizeof(struct kevent));
	ev.ident = fd;
	ev.filter = EVFILT_WRITE;
	ev.flags = EV_ADD|EV_CLEAR;
	if(kevent(kq,&ev,1,NULL,0,NULL)==-1)
	{
		err("kevent");
	}
}

// Global
char* remote_addr="127.0.0.1";
unsigned short port = 8888;
int kq;
int event_loop_num = 1;
int msg_interval = 1; 
int connections = 10;

void* event_loop(void* p)
{
	const int evlen = 10240;
	struct kevent evlist[evlen];
	for(;;)
	{
		int n = kevent(kq,NULL,0,evlist,evlen,NULL);
		if(n==-1)
		{
			err("kevent");
		}
		int i;
		for(i=0;i<n;i++)
		{
			int fd = evlist[i].ident;
			int flags = evlist[i].flags;
			int data = evlist[i].data;
			if(flags & EV_ERROR)
			{
				printf("Error:%s\n",strerror(data));
				exit(data);
			}
			struct sockaddr_in addr;
			socklen_t len = sizeof(addr);
			if(getsockname(fd,(struct sockaddr*)&addr,&len)==-1)
			{
				err("getsockname");
			}
			//sleep(1);
		}
	}
	return NULL;
}

int main(int argc,char** argv)
{
	if(argc>1)
	{
		remote_addr = argv[1];
	}

	if(argc>2)
	{
		port = atoi(argv[2]);
	}

	printf("Addr:%s:%d\n",remote_addr,port);

	kq = kqueue();
	if(kq==-1)
	{
		perror("kqueue");
		return -1;
	}
	struct sockaddr_in rmtaddr_in;
	rmtaddr_in.sin_family = AF_INET;
	rmtaddr_in.sin_port = htons(port);
	inet_aton(remote_addr,&rmtaddr_in.sin_addr);

	socklen_t socklen = sizeof(struct sockaddr_in);

	int i;
	for(i=0;i<connections;i++)
	{
		int sock = socket(PF_INET,SOCK_STREAM,0);
		if(sock==-1)
		{
			err("socket");
		}

		if(fcntl(sock,F_SETFL,O_NONBLOCK)==-1)
		{
			err("fcntl");
		}

		if(connect(sock,(struct sockaddr*)&rmtaddr_in,socklen)==-1)
		{
			if(errno!=EINPROGRESS)
			{
				err("connect");
			}
		}
		reg_write_fd(kq,sock);
	}

	// start event loop
	pthread_t *threads = malloc(sizeof(pthread_t)*event_loop_num);
	for(i=0;i<event_loop_num;i++)
	{
		pthread_create(&threads[i],NULL,event_loop,NULL);
	}

	printf("done\n");
	getchar();
	return 0;
}


