#include "sort-test.h"

void do_insertionsort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *tmpSwap;
    uint32_t *x, *cpos;

    x = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    tmpSwap = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    cpos = (uint32_t*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );

    for( *x = 1; *x < ( asize ); (*x)++ )
    {
        *cpos = *x;

        // take it to the top
        do
        {
            if( sortlist[ *cpos ] < sortlist[ *cpos - 1 ] )
            {
                //swap them
                *tmpSwap = sortlist[ *cpos - 1 ];
                sortlist[ *cpos - 1 ] = sortlist[ *cpos ];
                sortlist[ *cpos ] = *tmpSwap;
            }

            (*cpos)--;
            sortStats->iter++;
            
            if( *cpos < 1 )
                *cpos = 1;

        } while( sortlist[ *cpos ] < sortlist[ *cpos - 1 ] &&
                 *cpos > 0 );
    }

    sortStats->memFree( (char*) x, sortStats );
    sortStats->memFree( (char*) tmpSwap, sortStats );
    sortStats->memFree( (char*) cpos, sortStats );
    
    return;
}

