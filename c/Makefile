executable=test 
objects=test.o

all:$(executable) pipe

$(executable):%:%.o
	gcc -g -lreadline -o $@ $<
$(objects):%.o:%.c
	gcc -g -c -o $@ $<


clean:
	rm -f $(objects) $(executable)
