#include "inc.h"

#define DEPTH 100000

void do_mk_and_chg();

int main(int argc,char** argv)
{
	do_mk_and_chg(0);
	return 0;
}

void do_mk_and_chg(int depth)
{
	if(depth>=DEPTH)
	{
		char *buf=malloc(1024*1024);
		if(NULL==getcwd(buf,1024*1024))
		{
			perror("get cwd error");
		}
		printf("depth:%d,working dir:%s\n",depth,buf);
		free(buf);
		return;
	}
	char* dirname="dir";
	if(-1==mkdir(dirname,0777))
	{
		printf("depth:%d\n",depth);
		perror("mkdir error");
	}
	if(-1==chdir(dirname))
	{
		printf("depth:%d\n",depth);
		perror("chdir error");
	}
	do_mk_and_chg(depth+1);
}
