#include <stdio.h>
#include "dbg_util.h"


void print_byte(void* ptr,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%hhd\t",((char*)ptr)[i]);
	printf("\n");
}

void print_char(char* str,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%c,",str[i]);
	printf("\n");
}

void num_to_str(int n)
{
	char str[1024];
	bzero(str,1024);
	int i=0;
	int tmp=0;
	while(n>0)
	{
		tmp=n % 10;
		str[i]=tmp+'0';
		n=n/10;
		++i;
	}
	printf("str:%s\n",str);
}
