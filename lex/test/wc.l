%{
int chars=0;
int words=0;
int lines=0;
%}

%%

.						 {printf("others\n");}
[a-zA-Z]+    {printf("words\n");}
\n					 {printf("line\n");}

%%

int main()
{
	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}
