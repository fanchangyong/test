#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("Usage:./a.out <str> <shift>\n");
		return -1;
	}
	char* str = strdup(argv[1]);
	int len = strlen(str);
	int shift = atoi(argv[2]);

	int i;
	for(i=0;i<shift;i++)
	{
		int j;
		char t=str[0];
		for(j=1;j<len;j++)
		{
			str[j-1]=str[j];
		}
		str[j-1]=t;
	}
	printf("str:%s\n",str);
	free(str);
	return 0;
}
