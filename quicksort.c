
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

const int QS_MAX_LEVELS = 10000;

void cleanup( int *piv, int *beg, int *end, int64_t *i, int64_t *L, int64_t *R, STATS *sortStats )
{
    sortStats->memFree( (char*) piv, sortStats );
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) beg, sortStats );
    sortStats->memFree( (char*) end, sortStats );
    sortStats->memFree( (char*) L, sortStats );
    sortStats->memFree( (char*) R, sortStats );
}

void do_quicksort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *piv, *beg, *end;
    int64_t *i, *L, *R;
    
    piv = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    i = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    beg = (int*) sortStats->memAlloc( sizeof( int ) * QS_MAX_LEVELS, sortStats );
    end = (int*) sortStats->memAlloc( sizeof( int ) * QS_MAX_LEVELS, sortStats );
    
    L = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    R = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );

    *i = 0;
    beg[ 0 ] = 0;
    end[ 0 ] = (int) asize;

    while( *i >= 0 )
    {
        *L = beg[ *i ];
        *R = end[ *i ] - 1;
        if( *L < *R )
        {
            *piv = sortlist[ *L ];
            if( *i == QS_MAX_LEVELS - 1 )
            {
                cleanup( piv, beg, end, i, L, R, sortStats );
                return;
            }

            while( *L < *R )
            {
                while( ( ( *L < *R ) && sortlist[ *R ] >= *piv ) )
                {
                    (*R)--;
                    sortStats->iter++;
                }

                if( *L < *R )
                {
                    sortlist[ (*L)++ ] = sortlist[ *R ];
                }

                while( ( ( *L < *R ) && sortlist[ *L ] <= *piv ) )
                {
                    (*L)++;
                    sortStats->iter++;
                }

                if( *L < *R )
                {
                    sortlist[ (*R)-- ] = sortlist[ *L ];
                }
            }

            sortlist[ *L ] = *piv;
            beg[ *i + 1 ] = *L + 1;
            end[ *i + 1 ] = end[ *i ];
            end[ (*i)++ ] = *L;
        }
        else
        {
            (*i)--;
            sortStats->iter++;
        }
    }

    cleanup( piv, beg, end, i, L, R, sortStats );    
    return;
}
