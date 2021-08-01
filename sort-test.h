#ifndef __ST_H__
#define __ST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define TRUE                1
#define FALSE               (!TRUE) 

#define SHOW_SORTED_LIST    FALSE
#define SHOW_ISSUES         FALSE
#define SHOW_DEACTIVE_NORM  TRUE
#define SHOW_DEACTIVE_HUGE  FALSE

#define MAX_STRING_SIZE     1024

#define ST_BALANCED         0       // evenly distributed random numbers over the entire range
#define ST_CENTRE_WEIGHT    1
#define ST_TOP_WEIGHT       2
#define ST_BOT_WEIGHT       3

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
typedef struct      sortplan_def        SORT;
typedef struct      algorithm_def       ALGORITHM;
typedef struct      stats_def           STATS;
typedef void        ( *sortFun )        ( int *, uint32_t, STATS * );
typedef char *      ( *allocMemFun )    ( size_t, STATS * );
typedef void        ( *freeMemFun )     ( char *, STATS * );

// Struct definitions
struct sortplan_def
{
    char *sortName;
    uint32_t size;
    int lowerlimit;
    int upperlimit;
    int active;
    int isHuge;
    int sortType;
};

struct algorithm_def
{
    char *algorithmName;
    int active;
    int runHuge;
    sortFun sortModule;
};

struct stats_def
{
    SORT *sortUsed;
    ALGORITHM *algoUsed;
    allocMemFun memAlloc;       // these mem routines don't need to be in the stats_def... need to consider taking them out
    freeMemFun memFree;
    uint64_t memoryUsed;       // Bytes
    uint64_t iter;             // Lowest level loop iterations
};

// Extern definitions
extern const SORT sortRunPlan[];
extern const ALGORITHM sortAlgorithms[];
extern const uint totalSortRuns;
extern const uint totalSortAlgorithms;
                            
// sort functions
void do_bubblesort      ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_insertionsort   ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_quicksort       ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_gnomesort       ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_combsort        ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_timsort         ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_radixsort       ( int *sortlist, uint32_t asize, STATS *sortStats );

// math.c functions
int randNumGen              ( int min, int max );
int randNumGen_skewed       ( int min, int max, float skew );

// mem.c functions
char *salloc_mem( size_t size, STATS *sortStats );
void sfree_mem( char *memptr, STATS *sortStats );

#endif
