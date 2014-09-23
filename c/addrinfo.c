#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>

int main(int argc,char** argv)
{
	struct addrinfo hints;
	bzero(&hints,sizeof(hints));
	hints.ai_family = PF_LOCAL;

	struct addrinfo *res;
	if(getaddrinfo("www.baidu.com",NULL,&hints,&res)!=0)
	{
		printf("getaddrinfo error\n");
		return -1;
	}
	
	struct addrinfo *restmp = res;
	for(;restmp!=NULL;restmp=restmp->ai_next)
	{
		struct sockaddr_in * iaddr = (struct sockaddr_in*)restmp->ai_addr;
		printf("ip:%s\n",inet_ntoa(iaddr->sin_addr));
	}
}
