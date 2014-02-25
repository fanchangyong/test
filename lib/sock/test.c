#include <stdio.h>
#include "sock_util.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define LISTEN_PORT 8888


int main()
{
	int sock;
	start_tcp_server(8888,&sock);	
		
}
