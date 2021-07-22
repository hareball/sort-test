CC=gcc
CLEAN=rm
CFLAGS=-Wall -Werror -Ofast -s
LDFLAGS=
OBJECTS=sort-test.o bubblesort.o insertionsort.o quicksort.o gnomesort.o combsort.o timsort.o

sort-test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sort-test $(LDFLAGS)

clean:
	$(CLEAN) -f $(OBJECTS)
