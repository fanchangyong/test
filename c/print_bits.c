#include <stdio.h>

void print_bits(char* p,int len)
{
	int i;
	for(i=len-1;i>=0;i--)
	{
		int j;
		for(j=7;j>=0;j--)
		{
			if((1<<j) & (p[i]))
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		printf(" ");
		if(i>0 && i%4==0)
			printf("\n");
	}
	printf("\n");
}

int main()
{
	unsigned char num = 0xff;
	print_bits((char*)&num,sizeof(num));
	return 0;
}
