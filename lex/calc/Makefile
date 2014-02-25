parser:	lex.yy.o y.tab.o Makefile
	cc -o parser lex.yy.o y.tab.o
lex.yy.c: calc.l y.tab.h
	lex calc.l

lex.yy.o: lex.yy.c
	cc -o lex.yy.o -c lex.yy.c

y.tab.c: calc.y
	yacc -d calc.y

y.tab.h: calc.y
	yacc -d calc.y

y.tab.o: y.tab.c y.tab.h
	cc -o y.tab.o -c y.tab.c

clean:
	rm -f parser lex.yy.c y.tab.c y.tab.h y.tab.o
