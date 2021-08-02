
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
 
#include "sort-test.h"

void do_combsort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *tmpSwap, *sorted;
    uint32_t *gap, *i;
    float *shrink;

    tmpSwap = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    gap = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    shrink = (float*) sortStats->memAlloc( sizeof( float ), sortStats );
    sorted = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    i = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    
    *tmpSwap = 0;
    *gap = asize;
    *shrink = 1.3f;
    *sorted = 0;
    
    do
    {
        *gap = floor( *gap / *shrink );
        if( *gap < 1 )
        {
            *gap = 1;
            *sorted = 1;
        }

        *i = 0;

        while( ( *i + *gap ) < asize )
        {
            if( sortlist[ *i ] > sortlist[ *i + *gap ] )
            {
                *tmpSwap = sortlist[ *i ];
                sortlist[ *i ] = sortlist[ *i + *gap ];
                sortlist[ *i + *gap ] = *tmpSwap;
                *sorted = 0;
            }

            (*i)++;
            sortStats->iter++;
        }

    } while( !*sorted );
    
    sortStats->memFree( (char*) tmpSwap, sortStats );
    sortStats->memFree( (char*) gap, sortStats );
    sortStats->memFree( (char*) shrink, sortStats );
    sortStats->memFree( (char*) sorted, sortStats );
    sortStats->memFree( (char*) i, sortStats );

    return;
}
