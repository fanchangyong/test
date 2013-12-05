#include "inc.h"

int main(int argc,char** argv)
{
	struct utsname buf;
	int n=uname(&buf);
	if(n==-1)
		perror("uname");
	printf("sysname:%s\n",buf.sysname);
	printf("nodename:%s\n",buf.nodename);
	printf("reelease:%s\n",buf.release);
	printf("version:%s\n",buf.version);
	printf("machine:%s\n",buf.machine);

	char hostname[1024];
	if(-1==gethostname(hostname,1024))
		perror("gethostname");
	printf("hostname:%s\n",hostname);

	time_t tmbuf;
	if(-1==time(&tmbuf))
		perror("time");
	printf("time:%d\n",tmbuf);
}
