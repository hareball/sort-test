#include "sort-test.h"

/*
 * Tim sort based on code from Geeksforgeeks.com
 */
 
const int RUN = 32;

void insertionSort( int *arr, int left, int right, STATS *sortStats )
{
    int *i, *temp, *j;
    
    i = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    temp = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    j = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    for( *i = left + 1; *i <= right; (*i)++ )
    {
        *temp = arr[ *i ];
        *j = *i - 1;
        while( *j >= left && arr[ *j ] > *temp )
        {
            arr[ *j + 1 ] = arr[ *j ];
            (*j)--;
            sortStats->iter++;
        }
        arr[ *j + 1 ] = *temp;
    }
    
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) temp, sortStats );
    sortStats->memFree( (char*) j, sortStats );
}

void merge( int *arr, int l, int m, int r, STATS *sortStats )
{
    int *len1, *len2, *left, *right, *i, *j, *k;
    
    len1 = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    len2 = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    i = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
 
    *len1 = m - l + 1;
    *len2 = r - m;
    
    left = (int*) sortStats->memAlloc( sizeof( int ) * *len1, sortStats );
    right = (int*) sortStats->memAlloc( sizeof( int ) * *len2, sortStats );
    
    for( *i = 0; *i < *len1; (*i)++ )
        left[ *i ] = arr[ l + *i ];
    for( *i = 0; *i < *len2; (*i)++ )
        right[ *i ] = arr[ m + 1 + *i ];

    j = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    k = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    *i = 0;
    *j = 0;
    *k = l;
    
    while( *i < *len1 && *j < *len2 )
    {
        if( left[ *i ] <= right[ *j ])
        {
            arr[ *k ] = left[ *i ];
            (*i)++;
        }
        else
        {
            arr[ *k ] = right[ *j ];
            (*j)++;
        }
        (*k)++;
        sortStats->iter++;
    }

    while ( *i < *len1 )
    {
        arr[ *k ] = left[ *i ];
        (*k)++;
        (*i)++;
        sortStats->iter++;
    }

    while ( *j < *len2 )
    {
        arr[ *k ] = right[ *j ];
        (*k)++;
        (*j)++;
        sortStats->iter++;
    }
    
    sortStats->memFree( (char*) len1, sortStats );
    sortStats->memFree( (char*) len2, sortStats );
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) left, sortStats );
    sortStats->memFree( (char*) right, sortStats );
    sortStats->memFree( (char*) j, sortStats );
    sortStats->memFree( (char*) k, sortStats );
    
}

void do_timsort( int *sortlist, uint32_t asize, STATS *sortStats )
{
    int *n, *i, *size, *left, *mid, *right;
    
    n = (int*) sortStats->memAlloc( sizeof( uint32_t ), sortStats );
    i = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    size = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    left = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    mid = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    right = (int*) sortStats->memAlloc( sizeof( int ), sortStats );
    
    *n = asize;

    for( *i = 0; *i < *n; (*i) += RUN )
        insertionSort( sortlist, *i, MIN( ( *i + RUN - 1 ), ( *n - 1 ) ), sortStats );

    for( *size = RUN; *size < *n; (*size) = 2 * (*size) )
    {
        for( *left = 0; *left < *n; (*left) += 2 * (*size) )
        {
            *mid = *left + *size - 1;
            *right = MIN( ( *left + 2 * (*size) - 1 ), ( *n - 1 ) );

            if( *mid < *right )
                merge( sortlist, *left, *mid, *right, sortStats );
            else
                sortStats->iter++;
        }
    }
    
    sortStats->memFree( (char*) n, sortStats );
    sortStats->memFree( (char*) i, sortStats );
    sortStats->memFree( (char*) size, sortStats );
    sortStats->memFree( (char*) left, sortStats );
    sortStats->memFree( (char*) mid, sortStats );
    sortStats->memFree( (char*) right, sortStats );

    return;
}
