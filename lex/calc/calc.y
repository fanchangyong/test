%{
#include <stdio.h>
int yylex();
int yyerror();
%}

%token NUMBER
%token OPERATOR
%token EOL

%%
expression:	
					|NUMBER OPERATOR NUMBER
		  {
				return 1;
		  }
			;
%%


int main()
{
	while(yyparse());
	return 0;
}
