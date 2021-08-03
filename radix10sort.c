
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
 * Radix base 10 sort based on code from Geeksforgeeks.com
 */
 
#include "sort-test.h"

const int rbase10 = 10;
 
int getMax( int *arr, uint32_t n, STATS *sortStats )
{
    int *mx, *i;
    int retMax;
    
    mx = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    i = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    *mx = arr[ 0 ];
    for ( *i = 1; *i < n; (*i)++ )
    {
        if ( arr[ *i ] > *mx )
        {
            *mx = arr[ *i ];
        }
        sortStats->iter++;
    }
    retMax = *mx;
    
    sortStats->memFree( (char*) mx, sortStats );
    sortStats->memFree( (char*) i, sortStats );
    
    return( retMax );
}

void radixCountSort10( int *arr, uint32_t n, int exp, STATS *sortStats )
{  
    int *output, *i, *count;
    
    output = (int*) sortStats->memAlloc( sizeof( int ) * n, sortStats );
    i = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    count = (int*) sortStats->memAlloc( sizeof( int ) * rbase10, sortStats );
    
    for( *i = 0; *i < rbase10; (*i)++ )
    {
        count[ *i ] = 0;
        sortStats->iter++;
    }
         
    for( *i = 0; *i < n; (*i)++ )
    {
        count[ ( arr[ *i ] / exp ) % rbase10 ]++;
        sortStats->iter++;
    }
 
    for( *i = 1; *i < rbase10; (*i)++ )
    {
        count[ *i ] += count[ *i - 1 ];
        sortStats->iter++;
    }
 
    for( *i = n - 1; *i >= 0; (*i)-- ) 
    {
        output[ count[ ( arr[ *i ] / exp ) % rbase10 ] - 1 ] = arr[ *i ];
        count[ ( arr[ *i ] / exp ) % rbase10 ]--;
        sortStats->iter++;
    }
 
    for( *i = 0; *i < n; (*i)++ )
    {
        arr[ *i ] = output[ *i ];
        sortStats->iter++;
    }
    
    sortStats->memFree( (char*) output, sortStats );
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) count, sortStats );
}
 
void do_radix10sort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *m, *exp;
    
    m = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    exp = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    *m = getMax( sortlist, asize, sortStats );

    for( *exp = 1; *m / *exp > 0; (*exp) *= rbase10 )
    {
        radixCountSort10( sortlist, asize, *exp, sortStats );
    }
    
    sortStats->memFree( (char*) m, sortStats );
    sortStats->memFree( (char*) exp, sortStats );
        
    return;
}
