#ifndef __ST_H__
#define __ST_H__

#define ARRAYSIZE               50000
#define QS_MAX_LEVELS           1000
#define SHOW_SORTED_LIST	0

// Function definitions
u_int64_t do_bubblesort( int *sortlist );
u_int64_t do_insertionsort( int *sortlist );
u_int64_t do_quicksort( int *sortlist );
u_int64_t do_gnomesort( int *sortlist );

#endif
