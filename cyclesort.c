
/*
 * sort-test
 * 
 * Copyright (C) 2022 Dan Hare
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

void do_cyclesort( int *sortlist, uint32_t asize, STATS *sortStats )
{   
    int *item;
    uint32_t *i, *pos, *cycle_start, *si;
    
    i = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    si = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    pos = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    item = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    cycle_start = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    
    *i = 0;
    *si = 0;
    *pos = 0;
    *item = 0;
    *cycle_start = 0;
    
    for( *cycle_start = 0; *cycle_start <= asize - 2; (*cycle_start)++ ) 
    {
        *item = sortlist[ *cycle_start ];
        *pos = *cycle_start;

        for( *i = *cycle_start + 1; *i < asize; (*i)++ )
        {
            if( sortlist[ *i ] < *item )
            {
                (*pos)++;
                sortStats->iter++;
			}
		}

        if( *pos == *cycle_start )
            continue;

        while( *item == sortlist[ *pos ] )
        {
			(*pos)++;
			sortStats->iter++;
		}

        if( *pos != *cycle_start ) 
        {
            swap( item, &sortlist[ *pos ] );
            sortStats->iter++;
        }

        while( *pos != *cycle_start ) 
        {	
            *pos = *cycle_start;

            for( *si = *cycle_start + 1; *si < asize; (*si)++ )
            {
                if( sortlist[ *si ] < *item )
                {
					(*pos)++;
					sortStats->iter++;
				}
			}
 
            while( *item == sortlist[ *pos ] )
            {
				(*pos)++;
				sortStats->iter++;
			}

            if( *item != sortlist[ *pos ] ) 
            {
				swap( item, &sortlist[ *pos ] );
                sortStats->iter++;
            }
        }
    }
     
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) si, sortStats );
    sortStats->memFree( (char*) pos, sortStats );
    sortStats->memFree( (char*) item, sortStats );
    sortStats->memFree( (char*) cycle_start, sortStats );

    return;
}
