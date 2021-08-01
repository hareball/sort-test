#include "sort-test.h"

const int QS_MAX_LEVELS = 10000;

void cleanup( int *piv, int *beg, int *end, int64_t *i, int64_t *L, int64_t *R, STATS *sortStats )
{
    sortStats->memFree( (char*) piv, sortStats );
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) beg, sortStats );
    sortStats->memFree( (char*) end, sortStats );
    sortStats->memFree( (char*) L, sortStats );
    sortStats->memFree( (char*) R, sortStats );
}

void do_quicksort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *piv, *beg, *end;
    int64_t *i, *L, *R;
    
    piv = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    i = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    beg = (int*) sortStats->memAlloc( sizeof( int ) * QS_MAX_LEVELS, sortStats );
    end = (int*) sortStats->memAlloc( sizeof( int ) * QS_MAX_LEVELS, sortStats );
    
    L = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );
    R = (int64_t*) sortStats->memAlloc( sizeof( int64_t ), sortStats );

    *i = 0;
    beg[ 0 ] = 0;
    end[ 0 ] = (int) asize;

    while( *i >= 0 )
    {
        *L = beg[ *i ];
        *R = end[ *i ] - 1;
        if( *L < *R )
        {
            *piv = sortlist[ *L ];
            if( *i == QS_MAX_LEVELS - 1 )
            {
                cleanup( piv, beg, end, i, L, R, sortStats );
                return;
            }

            while( *L < *R )
            {
                while( ( ( *L < *R ) && sortlist[ *R ] >= *piv ) )
                {
                    (*R)--;
                    sortStats->iter++;
                }

                if( *L < *R )
                {
                    sortlist[ (*L)++ ] = sortlist[ *R ];
                }

                while( ( ( *L < *R ) && sortlist[ *L ] <= *piv ) )
                {
                    (*L)++;
                    sortStats->iter++;
                }

                if( *L < *R )
                {
                    sortlist[ (*R)-- ] = sortlist[ *L ];
                }
            }

            sortlist[ *L ] = *piv;
            beg[ *i + 1 ] = *L + 1;
            end[ *i + 1 ] = end[ *i ];
            end[ (*i)++ ] = *L;
        }
        else
        {
            (*i)--;
            sortStats->iter++;
        }
    }

    cleanup( piv, beg, end, i, L, R, sortStats );    
    return;
}
