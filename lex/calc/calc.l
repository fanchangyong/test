%{

#include "y.tab.h"

%}

number [0-9]+
op [\+\-\*\/]


%%

{number}	{return NUMBER;}
{op}		{return OPERATOR;}

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

