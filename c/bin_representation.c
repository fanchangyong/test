#include <stdio.h>

char* i_to_b(int number,int len)
{
	int i;
	for(i=len-1;i>=0;--i)
	{
		char c=((number & (1<<i)) ? '1':'0');
		printf("%c",c);
	}
	printf("\n");
	return 0;
}

int main(int argc,char** argv)
{
	int i=0b11010100101000000000000000000001;
	i_to_b(i,sizeof(i)*8);
	char c=i;
	i_to_b(c,sizeof(c)*8);
	printf("%d,%d\n",i,c);	
	return 0;
}
