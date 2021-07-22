#ifndef __ST_H__
#define __ST_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SHOW_SORTED_LIST		0

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
typedef u_int64_t 	(*sortType)			(int *, int);
typedef struct 		sort_ref			SORT;

// Struct definitions
struct sort_ref
{
	int size;
	int isLarge;
};

// Function definitions
u_int64_t do_bubblesort		( int *sortlist, int asize );
u_int64_t do_insertionsort	( int *sortlist, int asize );
u_int64_t do_quicksort		( int *sortlist, int asize );
u_int64_t do_gnomesort		( int *sortlist, int asize );
u_int64_t do_combsort		( int *sortlist, int asize );
u_int64_t do_timsort		( int *sortlist, int asize );

#endif
