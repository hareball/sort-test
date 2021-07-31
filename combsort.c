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
