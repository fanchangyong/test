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
#include <sys/time.h>

struct fd_data
{
	int conn_flag;
	long conn_time_ms;
	long write_time_ms;
};

#define NOT_CONNECTED 0
#define CONNECTED     1

void err(char* str)
{
	perror(str);
	exit(1);
}

long now_us()
{
	struct timeval tp;
	struct timezone tz;
	if(gettimeofday(&tp,&tz)!=0)
	{
		perror("gettimeofday");
		return 1;
	}
	return tp.tv_sec*1000+tp.tv_usec;
}

void reg_write_fd(int kq,int fd,int conn_flag)
{
	struct kevent ev;
	bzero(&ev,sizeof(struct kevent));
	ev.ident = fd;
	ev.filter = EVFILT_WRITE;
	ev.flags = EV_ADD;
	struct fd_data *pdata = malloc(sizeof(struct fd_data));
	bzero(pdata,sizeof(*pdata));
	pdata->conn_flag = conn_flag;
	if(conn_flag==NOT_CONNECTED)
	{
		pdata->conn_time_ms = now_us();
	}
	else
	{
		pdata->write_time_ms = now_us();
	}
	
	ev.udata = pdata;
	
	if(kevent(kq,&ev,1,NULL,0,NULL)==-1)
	{
		err("kevent");
	}
}


// Global
char* remote_addr="10.3.0.138";
unsigned short port = 8888;
int kq;
int event_loop_num = 1;
int msg_interval = 1; 
int connections = 1000;
const int buf_size = 1025; 
int seconds = 1;

void write_data(int fd)
{
	static char buf[buf_size];
	if(write(fd,buf,buf_size)==-1)
	{
		if(errno!=EWOULDBLOCK)
		{
			err("write");
		}
	}
}

void* event_loop(void* p)
{
	for(;;)
	{
		const int evlen = 1024;
		struct kevent evlist[evlen];
		int n = kevent(kq,NULL,0,evlist,evlen,NULL);
		printf("n:%d\n",n);
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
			struct fd_data* pfddata = (struct fd_data*)(evlist[i].udata);

			int err_state;
			socklen_t err_len = sizeof(int);
			if(getsockopt(fd,SOL_SOCKET,SO_ERROR,&err_state,&err_len)==-1)
			{
				err("getsockopt");
			}
			if(err_state)
			{
				printf("err state:%s\n",strerror(err_state));
				exit(1);
			}
			if(flags & EV_ERROR)
			{
				printf("Error:%s\n",strerror(data));
				continue;
			}
			if(flags & EV_EOF)
			{
				printf("kevent EOF\n");
				continue;
			}
			struct sockaddr_in addr;
			socklen_t len = sizeof(addr);
			if(getsockname(fd,(struct sockaddr*)&addr,&len)==-1)
			{
				err("getsockname");
			}
			// connect ok
			if(pfddata->conn_flag==NOT_CONNECTED)
			{
				long now = now_us();
				reg_write_fd(kq,fd,CONNECTED);
				//write_data(fd);
			}
			else
			{
				long now = now_us();
				close(fd);
			}
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
	int i;

	printf("Addr:%s:%d\n",remote_addr,port);

	kq = kqueue();
	if(kq==-1)
	{
		perror("kqueue");
		return -1;
	}

	// start event loop
	pthread_t *threads = malloc(sizeof(pthread_t)*event_loop_num);
	for(i=0;i<event_loop_num;i++)
	{
		pthread_create(&threads[i],NULL,event_loop,NULL);
	}

	struct sockaddr_in rmtaddr_in;
	rmtaddr_in.sin_family = AF_INET;
	rmtaddr_in.sin_port = htons(port);
	inet_aton(remote_addr,&rmtaddr_in.sin_addr);

	socklen_t socklen = sizeof(struct sockaddr_in);

	int j;
	for(j=0;j<seconds;j++)
	{
		for(i=0;i<connections;i++)
		{
			int sock = socket(PF_INET,SOCK_STREAM,0);
			if(sock==-1)
			{
				err("socket");
			}

			int flags = fcntl(sock,F_GETFL,0);
			if(flags==-1)
			{
				err("fcntl");
			}

			if(fcntl(sock,F_SETFL,flags|O_NONBLOCK)==-1)
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
			else
			{
				printf("connected sync!\n");
			}
			reg_write_fd(kq,sock,NOT_CONNECTED);
		}
		sleep(1);
	}


	printf("done\n");
	getchar();
	return 0;
}


