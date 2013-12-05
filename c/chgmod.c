#include "inc.h"

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

// operation define
#define OP_ADD 		1
#define OP_REMOVE 2

int main(int argc,char** argv)
{
	if(argc!=4)
	{
		printf("Usage: test <op> <pathname> <mode>\n");
		return 1;
	}
	char* strop=argv[1];
	char* pathname=argv[2];
	char* strmode=argv[3];
	int op;
	if(strcmp(strop,"add")==0)
	{
		op=OP_ADD;	
	}
	else if(strcmp(strop,"remove")==0)
	{
		op=OP_REMOVE;
	}
	else
	{
		printf("Usage: <op> must be `add' or `remove'!\n");
		return 1;
	}
	int mode;
	if(strcmp(strmode,"ux")==0)
	{
		mode=S_IXUSR;
	}
	else if(strcmp(strmode,"gx")==0)
	{
		mode=S_IXGRP;
	}
	else if(strcmp(strmode,"gs")==0)
	{
		mode=S_ISGID;
	}
	else
	{
		printf("This mode don't support now!\n");
		return 1;
	}
	struct stat st;
	if(-1==stat(pathname,&st))
	{
		perror("stat error");
		return 1;
	}
	if(op==OP_ADD)
	{
		add_mode(pathname,st.st_mode,mode);
	}
	else if(op==OP_REMOVE)
	{
		remove_mode(pathname,st.st_mode,mode);
	}
	return 0;
}

int add_mode(char* pathname,mode_t orimode,mode_t addmode)
{
	if(chmod(pathname,orimode|addmode)==-1)
	{
		perror("add mode chmod error");
		return -1;
	}
	return 0;
}

int remove_mode(char* pathname,mode_t orimode,mode_t removemode)
{
	if(chmod(pathname,orimode&~removemode)==-1)
	{
		perror("remove mode chmod error");
		return -1;
	}
	return 0;
}
