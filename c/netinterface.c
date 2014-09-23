#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

char* get_af_name(int af)
{
	if(af==AF_LINK)
	{
		return "AF_LINK";
	}
	return itoa(af);
}

int main()
{
	struct ifaddrs* ifap;
	if(getifaddrs(&ifap)!=0)
	{
		perror("getifaddrs");
		return -1;
	}

	for(;ifap;ifap=ifap->ifa_next)
	{
		if(ifap->ifa_addr)
		{
			if(ifap->ifa_addr->sa_family==AF_INET)
			{
				char* str_addr = 
					inet_ntoa(((struct sockaddr_in*)ifap->ifa_addr)->sin_addr);
				printf("%s:%s\n",ifap->ifa_name,str_addr);
			}
			else
			{
				printf("%s,addr family:%s\n",
						ifap->ifa_name,get_af_name(ifap->ifa_addr->sa_family));
			}
		}
		else
		{
			printf("%s:*\n",ifap->ifa_name);
		}
	}
	return 0;
}
