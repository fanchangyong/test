#include <stdio.h>

struct s
{
	int n;
	float f;
	char c;
};



int main()
{
	size_t pos=(size_t)&((struct s*)0)->c;
	printf("offset of n:%ld\n",pos);
	return 0;
}
