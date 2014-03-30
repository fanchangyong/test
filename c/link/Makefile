all:util.dylib a.out

add.o:add.c
	cc -c add.c

util.dylib:add.o
	cc -dynamiclib -o util.dylib add.o

a.out:main.c
	cc main.c

.PHONY:clean

clean:
	rm -f a.out util.dylib *.o
