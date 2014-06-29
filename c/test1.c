#include <stdio.h>

int main(void) 
{
	FILE* pf = popen("ps -ef","r");
	if(!pf)
	{
		perror("popen");
		return -1;
	}

	char buf[1024];
	fread(buf,sizeof(buf),1,pf);

	printf("buf:%s\n",buf);

	return 0;
}
