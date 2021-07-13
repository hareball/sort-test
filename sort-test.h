#ifndef __ST_H__
#define __ST_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ARRAYSIZE               50000
#define QS_MAX_LEVELS           1000
#define SHOW_SORTED_LIST	0

// Type definitions
typedef u_int64_t (*sortType)(int *);

// Function definitions
u_int64_t do_bubblesort		( int *sortlist );
u_int64_t do_insertionsort	( int *sortlist );
u_int64_t do_quicksort		( int *sortlist );
u_int64_t do_gnomesort		( int *sortlist );
u_int64_t do_combsort		( int *sortlist );

#endif
