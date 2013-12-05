#include <stdio.h>

int main()
{
	FILE* fd=fopen("/dev/tty","w");
	fprintf(fd,"Hello,world!\n");
	return 0;
}
