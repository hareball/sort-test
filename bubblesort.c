#include "sort-test.h"

u_int64_t do_bubblesort( int *sortlist )
{
        int x = 0, tmpSwap = 0;
        u_int64_t iter = 0;

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

        return( iter );
}

