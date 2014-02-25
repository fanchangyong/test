%{

#include "y.tab.h"

%}

number [0-9]+
op [\+\-\*\/]
eof \n


%%

{number}	{return NUMBER;}
{op}		{return OPERATOR;}
{eof}		{return EOF;}

%%

int yyerror(char* err)
{
	printf("yyerror,err:%s,at line:%d\n",err,yylineno);
	return 0;
}

int yywrap()
{
	return 1;
}

