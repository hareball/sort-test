
rtest:	sort-test.c
	gcc -Wall -Werror -Ofast -s sort-test.c -o sort-test

clean:
	rm -f sort-test
	rm -f sort-test.o
