#include "inc.h"

#define BUF_SIZE (1024*1024*1024) // 512MB

void check_src(char* );
void create_big_file(char* );
void chg_mod(char* );



int main(int argc,char** argv)
{
	char srcfile[]="./srcfile";
	char dstfile[]="./dstfile";

	check_src(srcfile);

	int srcfd=open(srcfile,O_SYNC|O_RDONLY);
	if(srcfd==-1)
		perror("open src file error");

	int dstfd=open(dstfile,O_SYNC|O_RDWR|O_CREAT);
	if(dstfd==-1)
		perror("open dst file error");
	chg_mod(dstfile);
	printf("copying file...\n");

	if(-1==lseek(srcfd,0,SEEK_SET))
		perror("seek source file error\n");

	if(-1==lseek(dstfd,0,SEEK_SET))
		perror("seek dst file error\n");

	time_t t1;
	time(&t1);

	char *buf=malloc(BUF_SIZE);
	size_t n;
	while(n=read(srcfd,buf,BUF_SIZE)>0)
		if(write(dstfd,buf,n)!=n)
			perror("write error\n");

	time_t t2;
	time(&t2);

	printf("time used:%ld\n",t2-t1);

	free(buf);
}

void check_src(char* filename)
{
	if(access(filename,F_OK)!=-1)
	{
		printf("deleting file:%s...\n",filename);
		if(-1==unlink(filename))
			perror("unlink error");
	}
	create_big_file(filename);
}

void create_big_file(char* filename)
{
	printf("creating big file...\n");
	int fd=open(filename,O_CREAT|O_RDWR);	
	if(fd==-1)
		perror("open big file error");
	chg_mod(filename);

	char *buf=malloc(BUF_SIZE);

	int i;
	for(i=0;i<BUF_SIZE;i+=4)
		*((int*)(buf+i))=i;

	if(write(fd,buf,BUF_SIZE)!=BUF_SIZE)
		perror("write to big file error");
	free(buf);
	close(fd);
}

void chg_mod(char* filename)
{
	int n=chmod(filename,S_IRUSR|S_IWUSR);
	if(-1==n)
		perror("chmod error");
}
