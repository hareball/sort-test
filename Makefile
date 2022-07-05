CC=gcc
CLEAN=rm
CFLAGS=-Wall -Werror -Ofast -s
LDFLAGS=-lm
OBJECTS=sort-test.o const.o math.o mem.o colour.o bubblesort.o insertionsort.o quicksort.o gnomesort.o combsort.o timsort.o radix10sort.o radix256sort.o heapsort.o cyclesort.o

sort-test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sort-test $(LDFLAGS)

clean:
	$(CLEAN) -f $(OBJECTS)
