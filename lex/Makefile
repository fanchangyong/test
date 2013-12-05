parser:	lex.yy.c Makefile
	cc -o parser lex.yy.c 
lex.yy.c: ex.l
	lex ex.l

clean:
	rm -f parser lex.yy.c
