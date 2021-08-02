
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

void do_bubblesort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *tmpSwap, *haveSwapped;
    uint32_t *x;
    
    tmpSwap = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    x = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    haveSwapped = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    do
    {
        *haveSwapped = 0;

        for( *x = 0; *x < ( asize - 1 ); (*x)++ )
        {
            if( sortlist[ *x ] > sortlist[ *x + 1 ] )
            {
                //swap
                *tmpSwap = sortlist[ *x + 1 ];
                sortlist[ *x + 1 ] = sortlist[ *x ];
                sortlist[ *x ] = *tmpSwap;
                *haveSwapped = 1;
            }
            sortStats->iter++;
        }
    } while( *haveSwapped );
    
    sortStats->memFree( (char*) tmpSwap, sortStats );
    sortStats->memFree( (char*) x, sortStats );
    sortStats->memFree( (char*) haveSwapped, sortStats );
    
    return;
}
