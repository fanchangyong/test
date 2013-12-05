executable=test
objects=test.o
all:$(executable)
$(executable):%:%.o
	gcc -g -o $@ $<
$(objects):%.o:%.c
	gcc -g -c -o $@ $<


clean:
	rm -f $(objects) $(executable)
