#include <stdio.h>
#include <string.h>

int part_str(char* str,int start,int end)
{
	int i;
	for(i=start;i<=end;i++)
	{
		printf("%c",str[i]);
	}
	printf("\n");
	return 0;
}

int match(char* str,char *rule)
{
	int lenstr = strlen(str);
	int lenrule = strlen(rule);

	int i,j;

	
	int match_start = -1;
	int starring = 0;
	
	j = 0;
	for(i=0;i<lenstr;i++)
	{
		if(starring==1)
		{
			if(str[i]==rule[j+1])
			{
				starring=0;
				j+=2;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if(str[i]==rule[j] || rule[j]=='?')
			{
				if(match_start==-1)
					match_start = i;
				j++;
			}
			else if(rule[j]=='*')
			{
				if(match_start==-1)
					match_start = i;
				starring = 1;
			}
			else
			{
				match_start = -1;
				j = 0;
			}
		}

		if(j>=lenrule)
		{
			part_str(str,match_start,i);
			j=0;
			starring = 0;
			match_start = -1;
		}
	}
	return 0;
}

int main(int argc,char** argv)
{
	if(argc<3)
	{
		printf("Usage:./a.out <str> <rule>\n");
		return -1;
	}
	char* str = strdup(argv[1]);
	char* rule = strdup(argv[2]);
	match(str,rule);
	return 0;
}
