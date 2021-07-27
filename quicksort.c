#include "sort-test.h"

const int QS_MAX_LEVELS = 1000;

u_int64_t do_quicksort( int *sortlist, int asize )
{
    int  piv, beg[ QS_MAX_LEVELS ], end[ QS_MAX_LEVELS ], i = 0;

    u_int64_t iter = 0;

    beg[ 0 ] = 0;
    end[ 0 ] = asize;

    while( i >= 0 )
    {
        int L, R;

        L = beg[ i ];
        R = end[ i ] - 1;
        if( L < R )
        {
            piv = sortlist[ L ];
            if( i == QS_MAX_LEVELS - 1 )
            {
                return( iter );
            }

            while( L < R )
            {
                while( ( ( L < R ) && sortlist[ R ] >= piv ) )
                {
                    R--;
                    iter++;
                }

                if( L < R )
                {
                    sortlist[ L++ ] = sortlist[ R ];
                }

                while( ( ( L < R ) && sortlist[ L ] <= piv ) )
                {
                    L++;
                    iter++;
                }

                if( L < R )
                {
                    sortlist[ R-- ] = sortlist[ L ];
                }
            }

            sortlist[ L ] = piv;
            beg[ i + 1 ] = L + 1;
            end[ i + 1 ] = end[ i ];
            end[ i++ ] = L;
        }
        else
        {
            i--;
            iter++;
        }
    }

    return( iter );
}
