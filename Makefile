
rtest:	sort-test.c
	gcc -Wall -Werror -Ofast -s bubblesort.c insertionsort.c quicksort.c sort-test.c -o sort-test

clean:
	rm -f sort-test
	rm -f *.o
