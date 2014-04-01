#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char** argv)
{
	unsigned short i;
	for(i=2323;i<65535;i++)
	{
		struct sockaddr_in caddr;
		inet_aton("192.168.1.107",&caddr.sin_addr.s_addr);
		int sock = socket(PF_INET,SOCK_STREAM,0);
		caddr.sin_family=AF_INET;
		caddr.sin_port = htons(i);
		int ret;
		//printf("scanning:%d\n",i);
		ret=connect(sock,(struct sockaddr*)&caddr,sizeof(caddr));
		if(ret==0)
		{
			printf("success:%d\n",i);
		}
		else
		{
			//perror("fail");
		}
	}
	printf("DONE!\n");
	return 0;
}
