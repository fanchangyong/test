#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int mmap_read()
{
	int fd=open("mmap_test.txt",O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		return 1;
	}
	off_t len=lseek(fd,0,SEEK_END);
	void* p=mmap(0,len,PROT_NONE,MAP_FILE|MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
	{
		perror("mmap read");
		return 1;
	}
	if(-1==mprotect(p,10,PROT_READ))
	{
		perror("mprotect");
		return 1;
	}
	char* tp=(char*)p;
	int i;
	for(i=0;i<len+10;++i)
	{
		printf("i=%d\n",i);
		printf("%c",tp[i]);
	}
	return 0;
}

int main(int argc,char** argv)
{
return	mmap_read();

	int fd=open("mmap_test.txt",O_RDWR|O_CREAT);
	if(fd==-1)
	{
		printf("open failed\n");
		return 1;
	}
	int len=10240;
	if(lseek(fd,len,SEEK_SET)==-1)
		perror("lseek");
	char buf[]={0};
	if(write(fd,buf,sizeof(buf))==-1)
		perror("write");
	void* p=mmap(0,len,PROT_WRITE|PROT_READ,MAP_FILE|MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
	{
		perror("map failed:");
		return 1;
	}
	printf("p=%p\n",p);
	char* tp=p;
	int i;
	for(i=0;i<len;i+=2)
	{
		printf("i=%d\n",i);
		tp[i]='o';
		tp[i+1]='k';
	}
	close(fd);
	return 0;
}
