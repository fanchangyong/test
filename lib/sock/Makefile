testobjs=sock_util.o test.o
clientobjs=sock_util.o client.o

all:test client 

test:$(testobjs)
	cc -o $@ $^

client:$(clientobjs)
	cc -o $@ $^

.c.o:
	cc -c -o $@ $<


clean:
	rm -f $(clientobjs) $(testobjs) test
