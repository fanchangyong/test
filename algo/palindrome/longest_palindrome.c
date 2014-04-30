#include <stdio.h>
#include <string.h>


int is_palin(char* str,int start,int end)
{
	char* startp=str+start;
	char* endp=str+end;

	if(startp==endp)
		return 0;

	for(;;)
	{
		if(*startp==0 || *endp==0)
			break;
		
		if((*startp)!=(*endp))
		{
			return 0;
		}

		startp++;
		endp--;

		if(startp>=endp)
			break;
	}

	return 1;
}

void print_part(char* str,int start,int end)
{
	int i;
	for(i=start;i<=end;i++)
		printf("%c",str[i]);
	printf("\n");
}

char* longest_paline(char* str)
{
	int i;
	int len = strlen(str);

	int cur_max = 0;
	int start = -1;
	int end = -1;

	for(i=0;i<len;i++)
	{
		int j;
		for(j=i+1;j<len;j++)
		{
			if(is_palin(str,i,j))
			{
				if(j-i>cur_max)
				{
					cur_max = j-i;
					start = i;
					end = j;
				}
			}
		}
	}
	if(cur_max!=0)
		print_part(str,start,end);
	return 0;
}

int main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("./a.out <str>\n");
		return -1;
	}
	char* str = strdup(argv[1]);
	//printf("%d\n",is_palin(str,0,strlen(str)-1));
	longest_paline(str);
	return 0;
}
