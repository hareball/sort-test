#include "sort-test.h"

u_int64_t do_combsort( int *sortlist, int asize )
{
    int tmpSwap = 0;
    int gap = asize;
    float shrink = 1.3f;
    int sorted = 0;
    int i;
    u_int64_t iter = 0;

    do
    {
        gap = floor( gap / shrink );
        if( gap < 1 )
        {
            gap = 1;
            sorted = 1;
        }

        i = 0;

        while( ( i + gap ) < asize )
        {
            if( sortlist[ i ] > sortlist[ i + gap ] )
            {
                tmpSwap = sortlist[ i ];
                sortlist[ i ] = sortlist[ i + gap ];
                sortlist[ i + gap ] = tmpSwap;
                sorted = 0;
            }

            i++;
            iter++;
        }

    } while( !sorted );

    return( iter );
}
