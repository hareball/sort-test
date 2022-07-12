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
 * Bitonic Sort, c++ code originally from GeeksforGeeks.com
 */
 
#include "sort-test.h"

void compAndSwap( int a[], int i, int j, int dir )
{
    if( dir == ( a[ i ] > a[ j ] ) )
        swap( &a[ i ], &a[ j ] );
}

void bitonicMerge( int a[], int low, int cnt, int dir, STATS *sortStats )
{
    if( cnt > 1 )
    {
        int sk, i;
        
        sortStats->addStackMem( sizeof( sk ), sortStats );
        sortStats->addStackMem( sizeof( i ), sortStats );
        
        sk = cnt / 2;

        for( i = low; i < low + sk; i++ )
        {
            compAndSwap( a, i, i + sk, dir );
            sortStats->iter++;
        }
        bitonicMerge( a, low, sk, dir, sortStats );
        bitonicMerge( a, low + sk, sk, dir, sortStats );
    }
}

void bitonicSort( int a[], int low, int cnt, int dir, STATS *sortStats )
{
    if( cnt > 1 )
    {
        int k = cnt / 2;
        
        sortStats->addStackMem( sizeof( k ), sortStats );

        bitonicSort( a, low, k, 1, sortStats );
        bitonicSort( a, low + k, k, 0, sortStats );
        bitonicMerge( a, low, cnt, dir, sortStats );
    }   
}

void do_bitonicsort( int *sortlist, uint32_t asize, STATS *sortStats )
{
	bitonicSort( sortlist, 0, asize, 1, sortStats );
}

