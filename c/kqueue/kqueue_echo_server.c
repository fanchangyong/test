#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/uio.h>
#include <unistd.h>
#include <pthread.h>

#define BACKLOG 5
#define PORT 8888

// Global
int lsock = -1;
int kq = -1;
int thread_num = 4;

// Function declarations
void do_accept();
void do_read(int fd,int size);

void err(char* str)
{
	perror(str);
	exit(1);
}

void reg_read_fd(int kq,int fd)
{
	struct kevent evch;
	evch.ident = fd;
	evch.flags = EV_ADD;
	evch.filter = EVFILT_READ;
	if(kevent(kq,&evch,1,NULL,0,NULL)==-1)
	{
		err("kevent change event");
	}
}

void* event_loop(void* p)
{
	const int event_len = 1024;
	for(;;)
	{
		struct kevent evlist[event_len];
		int n = 0;
		if((n=kevent(kq,NULL,0,evlist,event_len,NULL))==-1)
		{
			err("kevent");
		}

		int i;
		for(i=0;i<n;i++)
		{
			int flags = evlist[i].flags;
			int fd = evlist[i].ident;
			int data = evlist[i].data;

			if(flags & EV_ERROR)
			{
				printf("err:%s\n",strerror(data));
				exit(0);
			}
			printf("flags:%d\n",flags);

			if(fd==lsock)
			{
				do_accept();
			}
			else
			{
				do_read(fd,data);
			}
		}
	}
}

void do_read(int fd,int size)
{
	char* buf = malloc(size);
	int nread = read(fd,buf,size);
	if(nread==-1)
	{
		err("read");
	}
	else if(nread==0)
	{
		printf("EOF\n");
		close(fd);
	}
	else
	{
		printf("Read:%s\n",buf);
	}
}

void do_accept()
{
	int clt_fd;
	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	if((clt_fd=accept(lsock,(struct sockaddr*)&caddr,&len))==-1)
	{
		err("accept");
	}
	else
	{
		printf("Client:%s:%d\n",inet_ntoa(caddr.sin_addr),caddr.sin_port);
		reg_read_fd(kq,clt_fd);
	}
}

int main(int argc,char** argv)
{
	kq = kqueue();
	if(kq==-1)
	{
		err("kqueue");
	}

	lsock = socket(PF_INET,SOCK_STREAM,0);
	if(lsock==-1)
	{
		err("socket");
	}
	
	struct sockaddr_in listn_addr;
	bzero(&listn_addr,sizeof(struct sockaddr_in));
	listn_addr.sin_family = AF_INET;
	listn_addr.sin_port = htons(PORT);
	listn_addr.sin_addr.s_addr = INADDR_ANY;

	// bind
	if(bind(lsock,(struct sockaddr*)&listn_addr,sizeof(listn_addr))==-1)
	{
		err("bind");
	}
	
	if(listen(lsock,BACKLOG)==-1)
	{
		err("listen");
	}

	reg_read_fd(kq,lsock);

	pthread_t *tids = malloc(thread_num*sizeof(pthread_t));
	int i;
	for(i=0;i<thread_num;i++)
	{
		pthread_t tid;
		pthread_create(&tids[i],NULL,event_loop,NULL);
	}

	for(i=0;i<thread_num;i++)
	{
		pthread_join(tids[i],NULL);
	}

	return 0;
}
