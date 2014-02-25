%{
#include <stdio.h>

#define WORD      	258
#define REDIRECT_IN 259
#define REDIRECT_OUT 260
#define REDIRECT_APPEND 261
%}

%%
[a-zA-Z_./]+      {return WORD;}
[ \t]					{/* ignored */}
"<"						{return REDIRECT_IN;}
">"						{return REDIRECT_OUT;}
">>"					{return REDIRECT_APPEND;}
%%

int main()
{
	int tok;
	while((tok=yylex()))
	{
		printf("tok:%d",tok);
		if(tok==WORD)
		{
			printf(":%s\n",yytext);
		}
		else
		{
			printf("\n");
		}
	}
	return 0;
}

int yywrap()
{
	return 0;
}
