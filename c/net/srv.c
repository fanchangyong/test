#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <strings.h>

void* do_accept(void* plfd);

int main(int argc,char** argv)
{
	int lfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in laddr;
	laddr.sin_family=AF_INET;
	laddr.sin_addr.s_addr = htonl(INADDR_ANY);
	laddr.sin_port = htons(8888);
	if(bind(lfd,(struct sockaddr*)&laddr,sizeof(laddr))!=0)
	{
		perror("bind");
		return 1;
	}

	if(listen(lfd,5)!=0)
	{
		perror("listen");
		return 1;
	}

	const int thread_num = 8;
	pthread_t pids[thread_num];

	int i;
	for(i=0;i<thread_num;i++)
	{
		pthread_t *pid=malloc(sizeof(pthread_t));
		bzero(pid,sizeof(*pid));
		printf("do_accept:%p\n",do_accept);
		int ret= pthread_create(pid,NULL,do_accept,&lfd);
		if(0!=ret)
		{
			perror("pthread_create");
		}
		pids[i]=*pid;
		//free(pid);
	}

	for(i=0;i<thread_num;i++)
	{
		void *result;
		pthread_join(pids[i],&result);
	}

	return 0;
}

void* do_accept(void *plfd)
{
	//printf("doaccept\n");
	//int lfd = *(int*)plfd;
	/*int lfd=0;*/
	/*printf("lfd:%d\n",lfd);*/
	/*for(;;)*/
	/*{*/
		/*int cfd;*/
		/*if(-1==(cfd=accept(lfd,NULL,NULL)))*/
		/*{*/
			/*perror("accept");*/
			/*return 0;*/
		/*}*/
		/*printf("a client connected\n");*/
		/*char buf[1024*1024*2];*/
		/*int ret;*/
		/*while((ret=read(cfd,buf,sizeof(buf)))>0)*/
		/*{*/
			/*printf("readed:%d\n",ret);*/
		/*}*/
		/*printf("read done:%d\n",ret);*/
	/*}*/

	printf("doaccept\n");
	return 0;
}
