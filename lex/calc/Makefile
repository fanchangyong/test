parser:	lex.yy.o y.tab.o Makefile
	cc -o parser lex.yy.o y.tab.o
lex.yy.c: calc.l
	lex calc.l

lex.yy.o: lex.yy.c
	cc -o lex.yy.o -c lex.yy.c

y.tab.c: calc.y
	yacc  -d calc.y

y.tab.o: y.tab.c
	cc -o y.tab.o -c y.tab.c

clean:
	rm -f parser lex.yy.c
