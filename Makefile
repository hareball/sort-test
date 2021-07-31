CC=gcc
CLEAN=rm
CFLAGS=-Wall -Werror -Ofast -s
LDFLAGS=-lm
OBJECTS=sort-test.o const.o math.o mem.o bubblesort.o insertionsort.o quicksort.o gnomesort.o combsort.o timsort.o radixsort.o

sort-test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sort-test $(LDFLAGS)

clean:
	$(CLEAN) -f $(OBJECTS)
