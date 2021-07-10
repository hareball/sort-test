#include <stdio.h>
#include <stdlib.h>

#include "sort-test.h"

void do_insertionsort( int *sortlist )
{
        int x = 0, tmpSwap = 0;
        long int iter = 0;

        for( x = 1; x < ( ARRAYSIZE ); x++ )
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

        printf( "[%ld iterations]... ", iter );

        return;
}

