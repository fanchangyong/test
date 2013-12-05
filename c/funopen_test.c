#include "inc.h"

int readfn(void* cookie,char* buf,int size)
{
	printf("calling readfn,cookie:%p,buf:%p,size:%d\n",cookie,buf,size);
	strncpy(buf,cookie,size);
	return 888;
}

int writefn(void* cookie,const char* buf,int size)
{
	strncpy(cookie,buf,size);
	return 888;
}

FILE* fmemopen(void* buf)
{
	FILE* fp=funopen(buf,readfn,writefn,NULL,NULL);
	printf("fropen return fp:%p\n",fp);
	return fp;
}

int main()
{
	char* buf=(char*)malloc(1024);
	bzero(buf,1024);
	strcpy(buf,"I'm inside buf");
	FILE* fp=fmemopen(buf);
	char* readbuf=(char*)malloc(1024);
	bzero(readbuf,1024);
	printf("buf:%p,readbuf:%p\n",buf,readbuf);
	size_t n=fread(readbuf,1024,1,fp);
	printf("fread return:%ld\n",n);
	printf("result buf,buf:%s,readbuf:%s\n",buf,readbuf);

	char* writebuf=(char*)malloc(1024);
	bzero(writebuf,1024);
	strcpy(writebuf,"I'm inside write buffer,hahha");
	fwrite(writebuf,1024,1,fp);

	printf("write result,buf:%s,readbuf:%s\n",buf,readbuf);
}
