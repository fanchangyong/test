#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>

long now_us()
{
	struct timeval tp;
	struct timezone tz;
	if(gettimeofday(&tp,&tz)!=0)
	{
		perror("gettimeofday");
		return 1;
	}
	return tp.tv_sec*1000*1000+tp.tv_usec;
}

int count = 1000;

int main()
{
	int i;
	long sum_latency = 0;
	for(i=0;i<count;i++)
	{

		int sock = socket(AF_INET,SOCK_STREAM,0);
		if(sock==-1)
		{
			perror("socket");
			return 1;
		}

		struct sockaddr_in remote;
		remote.sin_family = AF_INET;
		remote.sin_port = htons(8888);
		remote.sin_addr.s_addr = inet_addr("127.0.0.1");

		socklen_t len = sizeof(remote);

		long t1 = now_us();
		if(connect(sock,(struct sockaddr*)&remote,len)!=0)
		{
			perror("connect");
			return 1;
		}

		long t2 = now_us();
		sum_latency += (t2-t1);
	}
	printf("Average latency:%ld\n",sum_latency/count);
	return 0;
}
