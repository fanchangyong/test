/*
 * Test dup/dup2 syscall
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv)
{
	int fileno = 19;
	if(dup2(STDOUT_FILENO,fileno)==-1)
	{
		perror("dup2");
		exit(1);
	}

	char *buf="hello pipe";
	if(write(100,buf,strlen(buf)+1)==-1)
	{
		perror("write");
		return 1;
	}
	return 0;
}
