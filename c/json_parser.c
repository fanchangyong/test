//

#include <stdio.h>

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usage: ./a.out PATH\n");
		return 1;
	}

	char* path = argv[1];
	int fd = open(path,O_RDONLY);

	return 0;
}
