#include "sort-test.h"

u_int64_t do_gnomesort( int *sortlist )
{
        int pos = 0, tmpSwap = 0;
        u_int64_t iter = 0;

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

        return( iter );
}
