#include "sort-test.h"

u_int64_t do_insertionsort( int *sortlist, int asize )
{
    int x = 0, tmpSwap = 0;
    u_int64_t iter = 0;

    for( x = 1; x < ( asize ); x++ )
    {
        int cpos = x;

        // take it to the top
        do
        {
            if( sortlist[ cpos ] < sortlist[ cpos - 1 ] )
            {
                //swap them
                tmpSwap = sortlist[ cpos - 1 ];
                sortlist[ cpos - 1 ] = sortlist[ cpos ];
                sortlist[ cpos ] = tmpSwap;
            }

            cpos--;
            iter++;

        } while( sortlist[ cpos ] < sortlist[ cpos - 1 ] &&
                 cpos > 0 );
    }

    return( iter );
}

