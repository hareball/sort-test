#include <stdio.h>
#include <stdlib.h>

#include "sort-test.h"

void do_gnomesort( int *sortlist )
{
        int pos = 0, tmpSwap = 0;
        long int iter = 0;

	do
	{
		if( pos == 0 ||
		    sortlist[ pos ] >= sortlist[ pos - 1 ] )
		{
			pos++;
		}
		else
		{
			tmpSwap = sortlist[ pos ];
			sortlist[ pos ] = sortlist[ pos - 1 ];
			sortlist[ pos - 1 ] = tmpSwap;
			pos--;
		}

		iter++;


	} while( pos < ARRAYSIZE );

        printf( "[%ld iterations]... ", iter );

        return;
}
