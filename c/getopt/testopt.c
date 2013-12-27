#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


char* keylistp[]=
{
#define ONE 0
	"one",
#define TWO 1
	"two",
	NULL
};
void test_subopt(char* string)
{
	char* value;
	int c;
	while(*string)
	{
		switch(getsubopt(&string,keylistp,&value))
		{
			case ONE:
				printf("subopt is one,value is:%s\n",value);
				break;
			case TWO:
				printf("subopt is two,value is:%s\n",value);
				break;
			default:
				printf("unknown subopt\n");
				if(suboptarg)
				{
					printf("illegal sub option:%s\n",suboptarg);
				}
				else
				{
					printf("missing suboption arg\n");
				}
				break;
		}
	}
}

void test_getopt(int argc,char** argv)
{
	//optind=0;
	int c;
	while((c=getopt(argc,argv,"x:abcy:p::"))!=-1)
	{
		//printf("```optind:%d,optarg:%s,optopt:%c\n",optind,optarg,optopt);
		switch(c)
		{
			case 'x':
				printf("optarg of x is:%s\n",optarg);
				test_subopt(optarg);
				break;
			case 'y':
				printf("optarg of y is:%s\n",optarg);
				break;
			case 'p':
				//printf("optarg of p is:%s\n",optarg);
			case '?':
				break;
			default:
				printf("other option:%c\n",c);
				break;
		}
	}
	
}

void test_longopt(int argc,char** argv)
{
	struct option longopts[]={
		{"help",required_argument,NULL,'h'},
		{NULL,0,NULL,0}
	};
	int ch;
	while((ch=getopt_long(argc,argv,"h",longopts,NULL))!=-1)
	{
		printf("ch:%c\n",ch);
	}
}

int main(int argc,char** argv)
{
	char *cmds[]={
		"-x",
		"one",
		"two",
		"-ydef",
		"-abc",
		"-d",
		"-p",
		"789",
		"123"
	};


	int len=sizeof(cmds)/sizeof(char*);
	int i;
	char** copy_cmds;
	copy_cmds=malloc(sizeof(char*)*len);
	for(i=0;i<len;++i)
	{
		char* p=cmds[i];
		int slen=strlen(p);
		copy_cmds[i]=malloc(slen+1);	
		copy_cmds[i][slen]=0;
		strncpy(copy_cmds[i],p,slen);
	}
	if(argc==1)
	{
		optind=0;
		test_longopt(len,copy_cmds);
	}
	else
	{
		test_longopt(argc,argv);
	}

	return 0;
}
