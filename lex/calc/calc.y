%{

%}

%token NUMBER
%token OPERATOR

%%
expression:	NUMBER OPERATOR NUMBER
		  {
		  	printf("expression found\n");
		  }
%%


int main()
{
	yyparse();
	return 0;
}
