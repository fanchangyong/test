#include <stdio.h>
#include <string.h>

int is_palin(char* str)
{
	int len = strlen(str);
	int i;
	for(i=0;i<len/2;i++)
	{
		if(str[i]!=str[len-i-1])
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("Usgae:./a.out <str>\n");
		return -1;
	}
	char* str = strdup(argv[1]);
	int ispaline = is_palin(str);
	printf("is paline:%s\n",ispaline?"true":"false");
	return 0;
}
