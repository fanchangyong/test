#include <stdio.h>
#include <sys/event.h>
#include <time.h>

int wait(int nanosec)
{
	int kq = kqueue();
	if(kq==-1)
	{
		return 1;
	}

	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = nanosec;
	if(kevent(kq,NULL,0,NULL,0,&t)==-1)
	{
		perror("kevent");
		return -1;
	}
	return 0;
}

int main()
{
	printf("before\n");
	wait(1000);
	printf("after\n");
	return 0;
}
