all: server client test

server: server.c
	cc -o server -lev server.c

client: client.c
	cc -o client -lev client.c

test: test.c
	cc -o test -lev test.c

run:server
	@./server
