/*
 * UNIX DOMAIN SOCKET
 */

#include <strings.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

static int issrv = 0;
static const char sock_name[] = "./uds.sock";

int parse_flag(int argc,char** argv)
{
	for(;;)
	{
		int c;
		c = getopt(argc,argv,"s");
		if(c==-1)
			break;

		switch(c)
		{
			case 's':
				issrv = 1;
				break;
		}
	}
	return 0;
}

int do_srv()
{
	int listen_fd = socket(PF_UNIX,SOCK_STREAM,0);
	if(listen_fd==-1)
	{
		perror("socket");
		return -1;
	}

	if(unlink(sock_name)==-1)
	{
		if(errno!=ENOENT)
		{
			perror("unlink");
			return -1;
		}
	}

	struct sockaddr_un listen_addr;
	bzero(&listen_addr,sizeof(struct sockaddr_un));
	listen_addr.sun_family = PF_UNIX;
	strncpy(listen_addr.sun_path,sock_name,sizeof(listen_addr.sun_path));

	socklen_t addr_len = sizeof(struct sockaddr_un);
	if(bind(listen_fd,(const struct sockaddr*)&listen_addr,addr_len)==-1)
	{
		perror("bind");
		return -1;
	}

	if(listen(listen_fd,5)==-1)
	{
		perror("listen");
		return -1;
	}

	int cli_fd ;
	struct sockaddr_un cli_addr;
	socklen_t cliaddr_len = sizeof(struct sockaddr_un);
	while(( cli_fd = accept(listen_fd,(struct sockaddr*)&cli_addr,&cliaddr_len)) != -1)
	{
		for(;;)
		{
			char buf [1024];
			int n;
			n = read(cli_fd,buf,sizeof(buf));
			if(n==0)
			{
				printf("client close\n");
				break;
			}
			else if(n==-1)
			{
				perror("read");
				break;
			}
			else
			{
				printf("buf:%s",buf);
			}
			write(cli_fd,buf,sizeof(buf));
		}
	}

	return 0;
}

int do_cli()
{
	int fd = socket(PF_UNIX,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_un addr;
	bzero(&addr,sizeof(struct sockaddr_un));
	addr.sun_family = PF_UNIX;
	strncpy(addr.sun_path,sock_name,sizeof(addr.sun_path));

	socklen_t len = sizeof(struct sockaddr_un);

	if(connect(fd,(const struct sockaddr*)&addr,len)==-1)
	{
		perror("connect");
		return -1;
	}

	for(;;)
	{
		char buf[1024];
		read(STDIN_FILENO,buf,sizeof(buf));
		write(fd,buf,sizeof(buf)+1);

		char rbuf[1024];
		read(fd,rbuf,sizeof(rbuf));
		printf("from server:%s\n",rbuf);
	}

	return 0;
}

int main(int argc,char** argv)
{
	parse_flag(argc,argv);
	if(issrv)
	{
		do_srv();
	}
	else
	{
		do_cli();
	}
	return 0;
}
