#include <ev.h>


int main()
{
	ev_tstamp t = ev_time();
	printf("t :%f\n",t);
	return 0;
}
