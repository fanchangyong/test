#include <stdio.h>
#include <dlfcn.h>

int add(int,int);

int main()
{
	void* handle = dlopen("./util.dylib",RTLD_NOW);
	if(handle==NULL)
	{
		printf("Cannot find util.dylib!\n");
		return 1;
	}
	int (*addfunc)(int,int);
	addfunc = dlsym(handle,"add");
	int result=addfunc(5,6);
	printf("result is:%d\n",result);
	return 0;
}
