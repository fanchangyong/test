#include <stdio.h>
#include "sock_util.h"

int main(int argc,char** argv)
{
	int sock;
	start_tcp_server(8888,&sock);
 	return 0;
}
