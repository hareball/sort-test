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
