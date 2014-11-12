#include <stdio.h>
#include <unistd.h>

int main(int argc,char** argv)
{
	int i;
	for(i=0;i<20;i++)
	{
		int j;
		for(j=0;j<1000000;j++)
			;

		sleep(1);
	}
	return 0;
}
