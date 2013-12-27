executable=test 
objects=test.o

all:$(executable) pipe

$(executable):%:%.o
	gcc -g -o $@ $<
$(objects):%.o:%.c
	gcc -g -c -o $@ $<

pipe:pipe.o

clean:
	rm -f $(objects) $(executable)
