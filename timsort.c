#include "sort-test.h"

const int RUN = 32;

void insertionSort( int arr[], int left, int right, u_int64_t *iter )
{
    for( int i = left + 1; i <= right; i++ )
    {
        int temp = arr[ i ];
        int j = i - 1;
        while( j >= left && arr[ j ] > temp )
        {
            arr[ j + 1 ] = arr[ j ];
            j--;
            (*iter)++;
        }
        arr[ j + 1 ] = temp;
    }
}

void merge( int arr[], int l, int m, int r, u_int64_t *iter )
{
    int len1 = m - l + 1, len2 = r - m;
    int left[ len1 ], right[ len2 ];
    for( int i = 0; i < len1; i++ )
        left[ i ] = arr[ l + i ];
    for( int i = 0; i < len2; i++ )
        right[ i ] = arr[ m + 1 + i ];

    int i = 0;
    int j = 0;
    int k = l;

    while( i < len1 && j < len2 )
    {
        if( left[ i ] <= right[ j ])
        {
            arr[ k ] = left[ i ];
            i++;
        }
        else
        {
            arr[ k ] = right[ j ];
            j++;
        }
        k++;
        (*iter)++;
    }

    while ( i < len1 )
    {
        arr[ k ] = left[ i ];
        k++;
        i++;
        (*iter)++;
    }

    while ( j < len2 )
    {
        arr[ k ] = right[ j ];
        k++;
        j++;
        (*iter)++;
    }
}

u_int64_t do_timsort( int *sortlist, int asize )
{
    int n = asize;
    u_int64_t iter = 0;

    for( int i = 0; i < n; i += RUN )
        insertionSort( sortlist, i, MIN( ( i + RUN - 1 ), ( n - 1 ) ), &iter );

    for( int size = RUN; size < n; size = 2 * size )
    {
        for( int left = 0; left < n; left += 2 * size )
        {
            int mid = left + size - 1;
            int right = MIN( ( left + 2 * size - 1 ), ( n - 1 ) );

            if( mid < right )
				merge( sortlist, left, mid, right, &iter );
			else
				iter++;
        }
    }

    return( iter );
}
