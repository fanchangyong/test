// Memory management test

#include "inc.h"
#include <unistd.h>

typedef struct mm_block
{
	void* p;
	int len;
	struct mm_block* next;
}mm_block;

#define MAX_BLOCK 1024

struct mm_block* blocks[MAX_BLOCK];
int cur_count=0;

void* my_alloc(int size)
{
	mm_block* pm=sbrk(sizeof(mm_block));
	void* p=sbrk(size);	
	pm->p=p;
	pm->len=size;
	blocks[cur_count++]=pm;
	return p;
}

void my_free(void* ptr)
{
	int i;
	for(i=0;i<cur_count;++i)
	{
		if(ptr==blocks[i]->p)
		{
			if(-1==sbrk(-blocks[i]->len))
			{
				perror("sbrk");
			}
		}
	}
}

int main(int argc,char** argv)
{
	int* p=my_alloc(1024);
	printf("allocated p:%p\n",p);
	my_free(p);
	p[1000]=10;
	return 0;
}
