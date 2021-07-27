#include "sort-test.h"

int getMax( int *arr, int n, u_int64_t *iter )
{
    int mx = arr[ 0 ];
    for ( int i = 1; i < n; i++ )
    {
        if ( arr[ i ] > mx )
        {
            mx = arr[ i ];
        }
        (*iter)++;
    }
    return mx;
}

void countSort( int *arr, int n, int exp, u_int64_t *iter )
{
    int output[ n ];
    int i, count[ 10 ] = { 0 };
 
    for( i = 0; i < n; i++ )
    {
        count[ ( arr[ i ] / exp ) % 10 ]++;
        (*iter)++;
    }
 
    for( i = 1; i < 10; i++ )
    {
        count[ i ] += count[ i - 1 ];
        (*iter)++;
    }
 
    for( i = n - 1; i >= 0; i-- ) 
    {
        output[ count[ ( arr[ i ] / exp ) % 10 ] - 1 ] = arr[ i ];
        count[ ( arr[ i ] / exp ) % 10 ]--;
        (*iter)++;
    }
 
    for( i = 0; i < n; i++ )
    {
        arr[ i ] = output[ i ];
        (*iter)++;
    }
}
 
u_int64_t do_radixsort( int *sortlist, int asize )
{
    u_int64_t iter = 0;

    int m = getMax( sortlist, asize, &iter );

    for(int exp = 1; m / exp > 0; exp *= 10 )
    {
        countSort( sortlist, asize, exp, &iter );
    }
        
    return( iter );
}
