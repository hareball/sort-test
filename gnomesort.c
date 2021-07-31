#include "sort-test.h"

void do_gnomesort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *tmpSwap;
    uint32_t *pos;
    
    pos = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    tmpSwap = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    *pos = 0;
    
    do
    {
        if( *pos == 0 ||
            sortlist[ *pos ] >= sortlist[ *pos - 1 ] )
        {
            (*pos)++;
        }
        else
        {
            *tmpSwap = sortlist[ *pos ];
            sortlist[ *pos ] = sortlist[ *pos - 1 ];
            sortlist[ *pos - 1 ] = *tmpSwap;
            (*pos)--;
        }
        
        sortStats->iter++;
        
    } while( *pos < asize );

    sortStats->memFree( (char*) pos, sortStats );
    sortStats->memFree( (char*) tmpSwap, sortStats );
    
    return;
}
