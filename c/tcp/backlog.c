#include <stdio.h>
#include <sys/socket.h>

#define PORT 8888

void err(char* str)
{
	perror(str);
	exit(0);
}

int main()
{
	int sock = socket(PF_UNIX,SOCK_STREAM,0);
	if(sock==-1)
	{
		err("socket");
	}

	pid_t pid = fork();
	if(pid<0)
	{
		err("fork");
	}
	else if(pid==0) // child
	{

	}
	else // parent
	{
		struct sockaddr_in listen_addr;
		listen_addr.sin_family = PF_INET;
		listen_addr.sin_port = htons(PORT);
		bind(sock,);
	}


	return 0;
}
