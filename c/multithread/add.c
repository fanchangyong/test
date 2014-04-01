#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct worker_arg
{
	int start;
	int end;
};

const int64_t LEN = 10000000000;
const int CPU = 8;
int *arr;

void* worker(void* arg)
{
	struct worker_arg* worker_arg = (struct worker_arg*)arg;
	int start = worker_arg->start;
	int end = worker_arg->end;
	int i;
	int64_t *psum=malloc(sizeof(int64_t));
	*psum=0;
	for(i=start;i<end;i++)
	{
		*psum += arr[i];
	}
	return psum;
}

void init_arr()
{
	arr = malloc(sizeof(int64_t)*LEN);
	int64_t i;
	for(i=0;i<LEN;++i)
	{
		arr[i]=i;
	}
}

int main(int argc,char** argv)
{
	init_arr();
	int64_t work=LEN/CPU; // 每个线程需要处理的工作
	int i;
	pthread_t* threads=malloc(sizeof(pthread_t)*CPU);
	for(i=0;i<CPU;i++)
	{
		int64_t start_index = work*i;
		int64_t end_index = work*(i+1);
		struct worker_arg* arg=malloc(sizeof(struct worker_arg));
		arg->start = start_index;
		arg->end = end_index;
		int err=pthread_create(&threads[i],NULL,worker,arg);
		if(err!=0)
		{
			perror("pthread_create");
		}
	}

	int64_t sum=0;
	for(i=0;i<CPU;i++)
	{
		int64_t* worker_sum;
		pthread_join(threads[i],(void**)&worker_sum);
		sum+=*worker_sum;
	}
	printf("sum:%lld\n",sum);
	return 0;
}
