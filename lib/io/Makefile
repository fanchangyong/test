CC=cc
CFLAGS=
CPPFLAGS=
cfiles=io_util.c test.c
hfiles=io_util.h
objdir=obj
objs=io_util.o test.o
exec=test


all:$(objdir) $(exec) 


$(exec):$(objs) 
	cc -o $@ $^

$(objdir):
	mkdir $@

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.c
	$(CC) -MM $< > $@

include io_util.d
include test.d

.PHONY:clean

clean:
	rm -f $(objs) $(exec)
