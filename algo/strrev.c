#include <string.h>


void strrev(char* s)
{
	int i=0;
	int len=strlen(s);
	while(i<len/2)
	{
		char tmp=s[len-i-1];
		s[len-i-1]=s[i];	
		s[i]=tmp;
		i++;
	}
}
