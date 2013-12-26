objs=sock_util.o test.o
test:$(objs)
	cc -o $@ $^

.c.o:
	cc -c -o $@ $<


clean:
	rm -f $(objs) test
