#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

void print_host(struct hostent *phost)
{
	printf("official name:%s\n",phost->h_name);
	char** pptr;
	for(pptr=phost->h_aliases;*pptr!=NULL;pptr++)
	{
		printf("alias:%s\n",*pptr);
	}

	char str[1024];

	switch(phost->h_addrtype)
	{
		case AF_INET:
			for(pptr=phost->h_addr_list;*pptr!=NULL;pptr++)
			{
				printf("address:%s\n",inet_ntop(AF_INET,*pptr,str,sizeof(str)));
			}
	}
}

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("usage: ./a.out <addr>\n");
		return 1;
	}

	struct hostent* phost = gethostbyname(argv[1]);
	if(phost!=NULL)
		print_host(phost);
	else
		herror("gethostbyname");
	return 0;
}
