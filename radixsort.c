#include "sort-test.h"

/*
 * Radix sort based on code from Geeksforgeeks.com
 */
 
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

void countSort( int *arr, uint32_t n, int exp, STATS *sortStats )
{  
    int *output, *i, *count;
    
    output = (int*) sortStats->memAlloc( sizeof( int ) * n, sortStats );
    i = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    count = (int*) sortStats->memAlloc( sizeof( int ) * 10, sortStats );
    
    for( *i = 0; *i < 10; (*i)++ )
    {
        count[ *i ] = 0;
        sortStats->iter++;
    }
         
    for( *i = 0; *i < n; (*i)++ )
    {
        count[ ( arr[ *i ] / exp ) % 10 ]++;
        sortStats->iter++;
    }
 
    for( *i = 1; *i < 10; (*i)++ )
    {
        count[ *i ] += count[ *i - 1 ];
        sortStats->iter++;
    }
 
    for( *i = n - 1; *i >= 0; (*i)-- ) 
    {
        output[ count[ ( arr[ *i ] / exp ) % 10 ] - 1 ] = arr[ *i ];
        count[ ( arr[ *i ] / exp ) % 10 ]--;
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
 
void do_radixsort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *m, *exp;
    
    m = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    exp = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    *m = getMax( sortlist, asize, sortStats );

    for( *exp = 1; *m / *exp > 0; (*exp) *= 10 )
    {
        countSort( sortlist, asize, *exp, sortStats );
    }
    
    sortStats->memFree( (char*) m, sortStats );
    sortStats->memFree( (char*) exp, sortStats );
        
    return;
}
