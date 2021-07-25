#ifndef __ST_H__
#define __ST_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SHOW_SORTED_LIST	0

#define ST_BALANCED			0		// evenly distributed random numbers over the entire range
#define ST_CENTRE_WEIGHT	1
#define ST_TOP_WEIGHT		2
#define ST_BOT_WEIGHT		3

#define MAX(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define MIN(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

// Type definitions
typedef u_int64_t 	(*sortFun)		(int *, int);
typedef struct 		sort_ref		SORT;

// Struct definitions
struct sort_ref
{
	char *sortName;
	uint size;
	uint lowerlimit;
	uint upperlimit;
	int isLarge;
	int sortType;
};

// sort functions
u_int64_t do_bubblesort		( int *sortlist, int asize );
u_int64_t do_insertionsort	( int *sortlist, int asize );
u_int64_t do_quicksort		( int *sortlist, int asize );
u_int64_t do_gnomesort		( int *sortlist, int asize );
u_int64_t do_combsort		( int *sortlist, int asize );
u_int64_t do_timsort		( int *sortlist, int asize );

// math.c functions
int randNumGen				( int min, int max );
int randNumGen_skewed		( int min, int max, float skew );

#endif
