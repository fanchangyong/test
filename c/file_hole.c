#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main(int argc,char** argv)
{
	char buf1[]="abcdefghij";
	char buf2[]="ABCDEFGHIJ";

	int len1=strlen(buf1);
	int len2=strlen(buf2);

	int fd;
	if((fd=open("file.hole",O_RDWR|O_CREAT))<0)
		perror(argv[0]);
	if(write(fd,buf1,len1)!=len1)
		perror(argv[0]);

	if(lseek(fd,16384,SEEK_SET) == -1)
		perror(argv[0]);

	if(write(fd,buf2,len2)!=len2)
		perror(argv[0]);
	return 0;
}
