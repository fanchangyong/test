#include "inc.h"

#define BUF_SIZE (1024*1024*1024) // 512MB


void traverse_dir(DIR* dir);
int read_fd(char* pathname);

int main(int argc,char** argv)
{
	if(argc!=2)
	{
		printf("Usage: ./test <pathname>\n");
		return 1;
	}

	//char* pathname=malloc(strlen(argv[1])+1);
	//bzero(pathname,strlen(argv[1]+1));
	//strncpy(pathname,argv[1],strlen(argv[1]));
	char* pathname=argv[1];
	struct stat st;
	if(-1==stat(pathname,&st))
	{
		perror("stat error");
		return 1;
	}
	switch(S_IFMT&st.st_mode)
	{
		case S_IFDIR:
		{
			int fd=open(pathname,O_DIRECTORY);
			if(fd==-1)
			{
				perror("open error");
				return 1;
			}
			else
			{
				printf("open ok!\n");
				read_fd(pathname);
			}
		};
		break;
		default:
		{
			printf("pathname must be directory!\n");
		}
	}
	return 0;
}

int read_fd(char* pathname)
{
	DIR* dir=opendir(pathname);
	if(dir==NULL)
	{
		perror("opendir error");
	}
	traverse_dir(dir);
	return 0;
}

void traverse_dir(DIR* dir)
{
	while(1)
	{
		struct dirent* ent=readdir(dir);
		if(ent==NULL)
		{
			break;
		}
		printf("**name:%s\n",ent->d_name);
	}
}
