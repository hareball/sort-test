
rtest:	rtest.c   
	gcc -Wall -Werror -Ofast -s rtest.c -o rtest

clean:
	rm -f rtest
	rm -f rtest.o
