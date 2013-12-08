//Just to learn how to read from pipe
//Use method:
//./a.out < data.file
#include <stdio.h>

int main(int argc,char** argv)
{
	int n;
	for(;;)
	{
		printf("type what you want:");
		int ret=scanf("%d",&n);
		if(ret==EOF)
		{
			printf("Encountered eof,Stop\n");
			break;
		}
		else if(ret==0)
		{
			printf("Encounter invalid type,flushing buffer\n");
			fpurge(stdin);
		}
		else
		{
			printf("You just typed:%d\n",n);
		}
	}
	return 0;
}
