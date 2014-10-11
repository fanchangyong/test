#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

struct config
{
	int connections;
	char addr[128];
	unsigned short port;
	int thread_num;
};

struct event_loop_t
{
	int kq;
};

struct fired_event_t
{
	int kq;
	int fd;
	int bufsize;
};

typedef void (*cb_t)(void*);
void send_data(int fd,int size);

void parse_args(int argc,char** argv,struct config* conf)
{
	int ch;
	while((ch=getopt(argc,argv,"c:t:"))!=-1)
	{
		switch(ch)
		{
			case 'c':
				conf->connections = atoi(optarg);
				break;
			case 't':
				conf->thread_num = atoi(optarg);
				break;
		}
	}
	if(optind<argc)
	{
		strncpy(conf->addr,argv[optind],sizeof(conf->addr));
	}
	++optind;
	if(optind<argc)
	{
		conf->port = atoi(argv[optind]);
	}
	++optind;

	argc-=optind;
	argv+=optind;
}

// default config
void conf_def(struct config* conf)
{
	conf->connections = 10;
	strncpy(conf->addr,"127.0.0.1",sizeof(conf->addr));
	conf->port = 8888;
	conf->thread_num = 1;
}


void reg_write_fd(int kq,int fd,void* cb)
{
	struct kevent ev;
	EV_SET(&ev,fd,EVFILT_WRITE,EV_ADD|EV_CLEAR,0,0,cb);
	if(kevent(kq,&ev,1,NULL,0,NULL)==-1)
	{
		perror("kevent");
		exit(1);
	}
}

void write_cb(struct fired_event_t *fe)
{
	int buf_size = fe->bufsize;
	int fd = fe->fd;
	printf("Writable:%d\n",buf_size);
	send_data(fd,buf_size);
}

void conn_cb(struct fired_event_t *fe)
{
	printf("Connected\n");
	int fd = fe->fd;
	int kq = fe->kq;
	reg_write_fd(kq,fd,write_cb);
}

void send_data(int fd,int size)
{
	char* buf = malloc(size);
	ssize_t written = write(fd,buf,size);
	if(written==-1)
	{
		perror("write");
		//exit(1);
	}
	else
	{
		// Written successfully
		printf("written:%ld\n",written);
	}
}

void* event_loop(void* p)
{
	struct event_loop_t *loop = (struct event_loop_t*)p;
	int kq = loop->kq;
	struct kevent evlist[1024];
	for(;;)
	{
		int n = kevent(kq,NULL,0,evlist,1024,NULL);
		if(n==-1)
		{
			perror("kevent");
			exit(1);
		}
		int i;
		for(i=0;i<n;i++)
		{
			int fd = evlist[i].ident;
			int buf_size = evlist[i].data;
			int flags = evlist[i].flags;
			cb_t cb = (cb_t)(evlist[i].udata);

			if(flags&EV_ERROR)
			{
				perror("kevent");
				exit(1);
			}
			else if(flags & EV_EOF)
			{
				printf("EOF\n");
			}
			else
			{
				struct fired_event_t fe;
				fe.fd = fd;
				fe.kq = kq;
				fe.bufsize = buf_size;

				cb(&fe);
			}
		}
	}
	return NULL;
}

int main(int argc,char** argv)
{
	struct config conf;
	conf_def(&conf);
	parse_args(argc,argv,&conf);
	printf("** Configurations:\n");
	printf("Connections:[%d]\n",conf.connections);
	printf("Target:[%s:%d]\n",conf.addr,conf.port);

	int kq = kqueue();
	if(kq==-1)
	{
		perror("kqueue");
		exit(1);
	}

	struct sockaddr_in remote_addr;
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(conf.port);
	remote_addr.sin_addr.s_addr = inet_addr(conf.addr);
	socklen_t addrlen = sizeof(remote_addr);

	int i;
	for(i=0;i<conf.connections;i++)
	{
		int sock = socket(PF_INET,SOCK_STREAM,0);
		if(sock==-1)
		{
			perror("socket");
			exit(1);
		}
		
		// set nonblock
		int old_flags = fcntl(sock,F_GETFL);
		if(old_flags==-1)
		{
			perror("fcntl");
			exit(1);
		}
		if(fcntl(sock,F_SETFL,O_NONBLOCK)==-1)
		{
			perror("fcntl");
			exit(1);
		}
		
		if(connect(sock,(struct sockaddr*)&remote_addr,addrlen)==-1)
		{
			if(errno!=EINPROGRESS)
			{
				perror("connect");
				exit(1);
			}
		}
		reg_write_fd(kq,sock,conn_cb);
	}

	// Create Event Loop
	struct event_loop_t* loop_data = 
		malloc(sizeof(struct event_loop_t));
	loop_data->kq = kq;

	pthread_t *tids = malloc(sizeof(pthread_t)*conf.thread_num);
	for(i=0;i<conf.thread_num;i++)
	{
		pthread_create(&tids[i],NULL,event_loop,loop_data);
	}

	for(i=0;i<conf.thread_num;i++)
	{
		pthread_join(tids[i],NULL);
	}
	return 0;
}
