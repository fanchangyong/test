#include <stdio.h>
#include "stack.h"
#include <strings.h>
#include <stdlib.h>


cstack *ops_st;
cstack *val_st;

char* tmpstr;

char tmpnum[1024];

void tmp_num_to_st();

int calc(char* str)
{
	char c;
	while((c=(*str++)))
	{
		switch(c)
		{
			case '+':
				push(ops_st,'+');
				tmp_num_to_st();
				break;
			case '-':
				push(ops_st,'-');
				tmp_num_to_st();
				break;
			case ')':
				tmp_num_to_st();
				int v1=pop(val_st);
				char op=pop(ops_st);
				if(op=='+')
				{
					int v2=pop(val_st);
					push(val_st,v1+v2);
				}
				else if(op=='-')
				{
					int v2=pop(val_st);
					push(val_st,v1-v2);
				}
				break;
			case '(':
				break;
			default:
				bzero(tmpstr,2);
				strncpy(tmpstr,&c,1);
				strcat(tmpnum,tmpstr);
				break;
		}
	}
	return pop(val_st);
}

void tmp_num_to_st()
{
	if(*tmpnum!=0)
	{
		int i=atoi(tmpnum);
		printf("tmpnum:%s,i:%d\n",tmpnum,i);
		push(val_st,i);
		bzero(tmpnum,1024);
	}
}

int main(int argc,char** argv)
{
	tmpstr=malloc(sizeof(char)*2);
	bzero(tmpnum,1024);
	ops_st = create_stack(50);
	val_st = create_stack(50);
	int r=calc("((111+(3+5))+21)");
	printf("result:%d\n",r);
	return 0;
}
