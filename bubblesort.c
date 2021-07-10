#include <stdio.h>
#include <stdlib.h>

#include "sort-test.h"

void do_bubblesort( int *sortlist )
{
        int x = 0, tmpSwap = 0;
        long int iter = 0;

        do
        {
                tmpSwap = 0;

                for( x = 0; x < ( ARRAYSIZE - 1 ); x++ )
                {
                        if( sortlist[ x ] > sortlist[ x + 1 ] )
                        {
                                //swap
                                tmpSwap = sortlist[ x + 1 ];
                                sortlist[ x + 1 ] = sortlist[ x ];
                                sortlist[ x ] = tmpSwap;
                        }
                        iter++;
                }

        } while( tmpSwap );

        printf( "[%ld iterations]... ", iter );

        return;
}

