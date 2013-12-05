%{
#include <stdio.h>
int linenum;
int showtitle();
%}

int [0-9]+
float [0-9]*\.[0-9]+
line	[\n]
var	[a-zA-Z][a-zA-Z0-9]*
op	[\+\-\*\/\%]


%%

title showtitle();

{line}	++linenum;
{int}
	{
			printf("Int:%s\n",yytext);
	}
{float}	printf("float:%s,length:%ld\n",yytext,yyleng);
{var}	printf("Var:%s,length:%ld\n",yytext,yyleng);
{op} printf("Operator:%s\n",yytext);
.	

%%


int showtitle()
{
	printf("***Lex Example***\n");
	return 0;
}


int main()
{
	linenum=0;
	yylex();
	printf("\nLine count:%d\n",linenum);
	return 0;
}

int yywrap()
{
	return 1;
}
