
/*
 * sort-test
 * 
 * Copyright (C) 2021 Dan Hare
 *
 * This file is part of sort-test, a free suite of sort algorithms
 *
 * sort-test is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version
 *
 * sort-test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
 
#ifndef __ST_H__
#define __ST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define TRUE                1
#define FALSE               (!TRUE) 

#define SHOW_COLOUR         TRUE
#define SHOW_SORTED_LIST    FALSE
#define SHOW_ISSUES         FALSE
#define SHOW_DEACTIVE_NORM  TRUE
#define SHOW_DEACTIVE_HUGE  TRUE

#define MAX_STRING_SIZE     2048

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

#define COLOUR_START    "\033["
#define COLOUR_STOP     "^[[m"

// Foreground colours
#define CF_BLACK        ";30"           // @l
#define CF_RED          ";31"           // @r
#define CF_GREEN        ";32"           // @g
#define CF_YELLOW       ";33"           // @y
#define CF_BLUE         ";34"           // @b
#define CF_MAGENTA      ";35"           // @m
#define CF_CYAN         ";36"           // @c
#define CF_WHITE        ";37"           // @w

// Background colours
#define CB_BLACK        ";40"           // @kl
#define CB_RED          ";41"           // @kr
#define CB_GREEN        ";42"           // @kg
#define CB_YELLOW       ";43"           // @ky
#define CB_BLUE         ";44"           // @kb
#define CB_MAGENTA      ";45"           // @km
#define CB_CYAN         ";46"           // @kc
#define CB_WHITE        ";47"           // @kw

#define C_BOLD          ";1"
#define C_FLASH         ";5"
#define C_NORMAL        ";0"

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
void do_radix10sort     ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_radix256sort    ( int *sortlist, uint32_t asize, STATS *sortStats );
void do_heapsort        ( int *sortlist, uint32_t asize, STATS *sortStats );

// math.c functions
int randNumGen              ( int min, int max );
int randNumGen_skewed       ( int min, int max, float skew );

// mem.c functions
char *salloc_mem( size_t size, STATS *sortStats );
void sfree_mem( char *memptr, STATS *sortStats );

// sort-test.c functions
void write_log( char *fmt, ... );

// color.c functions
void add_colour( char *dest, const char *src );

// radix10sort.c
int getMax( int *arr, uint32_t n, STATS *sortStats );

#endif
