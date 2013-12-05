#include "inc.h"

void handler(int sig)
{
	signal(SIGINT,handler);
	signal(SIGABRT,handler);
	printf("calling handler\n");
}

int main(int argc,char** argv)
{
	signal(SIGINT,handler);
	signal(SIGABRT,handler);
	abort();
	pause();
	return 0;
}
