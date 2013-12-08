#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

char* i_to_b(int i)
{
	int len=1024;
	char* result=malloc(sizeof(char)*len);
	bzero(result,len);
	for(;;)
	{
		int m=i % 2;
		if(m==0)
			strcat(result,"0");
		else if(m==1)
			strcat(result,"1");
		else
			printf("error m:%d\n",m);
		i=i/2;
		if(i==0)
			break;
	}
	return result;
}
