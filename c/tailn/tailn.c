#include <stdio.h>

#define DEFAULT_OFFSET  512
#define READCOUNT 		10

void usage()
{
	printf("./tailn <filename>\n");
}

// go to last
int flast(FILE* fp)
{
	if(-1==fseek(fp,0,SEEK_END))
	{
		perror("fseek");
		return -1;
	}
	long pos=ftell(fp);
	if(pos>DEFAULT_OFFSET) // The file is longer than default offset
	{
		return fseek(fp,pos-DEFAULT_OFFSET,SEEK_SET);
	}
	else
	{
		return fseek(fp,0,SEEK_SET);
	}
	return 0;
}

int line_count(char* str)
{
	int line=0;
	char c;
	while((c=*str++))
	{
		if(c=='\n')
		{
			++line;
		}
	}
	return line;
}

void read_lines(FILE* fp)
{
	char buf[1024];
	fread(buf,1024,1,fp);
}

int main(int argc,char** argv)
{
	char* filename=NULL;
	if(argc<=1)
	{
		usage();
		return -1;
	}
	else
	{
		filename=argv[1];
	}
	FILE* fp=fopen(filename,"r");
	if(flast(fp)!=0)
	{
		perror("flast error");
	}
	char buf[1024];
	int ret=fread(buf,1024,1,fp);
	printf("buf:%s\n",buf);
	printf("lines :%d\n",line_count(buf));
	return 0;
}
