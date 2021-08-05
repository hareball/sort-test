
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
 
/* 
 *  To use this sort in your own program:
 *  ------------------------------------
 *  * Remove any sortStats lines, including the parameter
 *     --> Replace memAlloc and memFree calls with malloc and free
 *  * Pass in : pointer to the array that you want sorted (sortlist) 
 *            : size of array (asize)
 *  * You may need to copy some #includes from sort-test.h
 *  ------------------------------------
*/

/*
 * Heap sort based on code from Geeksforgeeks.com
 */
 
#include "sort-test.h"

static int64_t *largest, *l, *r;
static int *temp;

void swap( int *xp, int *yp )
{
    *temp = *xp;
    *xp = *yp;
    *yp = *temp;
}

void heapify( int *arr, int64_t n, int64_t i, STATS *sortStats )
{   
    *largest = i;
    *l = 2 * i + 1;
    *r = 2 * i + 2;
 
    if( *l < n && arr[ *l ] > arr[ *largest ] )
        *largest = *l;
 
    if( *r < n && arr[ *r ] > arr[ *largest ] )
        *largest = *r;

    if( *largest != i ) 
    {
        swap( &arr[ i ], &arr[ *largest ] );
        heapify( arr, n, *largest, sortStats );
    }
    
    sortStats->iter++;
}

void do_heapsort(int *sortlist, uint32_t asize, STATS *sortStats )
{
    int64_t *i;
    
    i = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    temp = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    largest = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    l = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    r = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    
    for( *i = ( asize / 2 ) - 1; *i >= 0; (*i)-- )
    {
        heapify( sortlist, asize, *i, sortStats );
    }
    
    for( *i = asize - 1; *i > 0; (*i)-- ) 
    {
        swap( &sortlist[ 0 ], &sortlist[ *i ] );
        heapify( sortlist, *i, 0, sortStats );
    }
    
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) temp, sortStats );
    sortStats->memFree( (char*) largest, sortStats );
    sortStats->memFree( (char*) l, sortStats );
    sortStats->memFree( (char*) r, sortStats );
}
