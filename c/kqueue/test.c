#include <stdio.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

void do_accept(int kfd,int fd)
{
	struct sockaddr_in cli_addr;
	socklen_t addr_len = sizeof(cli_addr);
	int cli_sock;
	if((cli_sock=accept(fd,(struct sockaddr*)&cli_addr,&addr_len))==-1)
	{
		perror("accept");
		return;
	}

	struct kevent changes[1];
	EV_SET(&changes[0],cli_sock,EVFILT_READ,EV_ADD,0,0,NULL);

	kevent(kfd,changes,1,NULL,0,NULL);

	// wait event
	while(1)
	{
		struct kevent events[1024];
		int n = kevent(kfd,NULL,0,events,1024,NULL);
		if(n==-1)
		{
			perror("kevent");
			return;
		}

		int i;
		for(i = 0;i<n;i++)
		{
			int fd = events[i].ident;
			int size = events[i].data;
			char *buf = malloc(size);
			recv(fd,buf,size,0);
			printf("size is:%d,buf:%s\n",size,buf);
		}
		
		printf("kevent result:%d\n",n);
	}
}

int main()
{
	int fd = socket(PF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket");
		return 1;
	}
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(fd,(struct sockaddr*)&addr,sizeof(addr))==-1)
	{
		perror("bind");
		return 1;
	}

	if(listen(fd,5)==-1)
	{
		perror("listen");
		return 1;
	}

	int kfd = kqueue();
	do_accept(kfd,fd);

	return 0;
}
