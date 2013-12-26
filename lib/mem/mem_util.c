#include "mem_util.h"
#include <stdio.h>

void print_byte(char* ptr,int len)
{
	int i;
	for(i=0;i<len;++i)
	{
		printf("%hhd\t",ptr[i]);
	}
}

int main()
{
	return 0;
}
