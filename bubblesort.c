#include "sort-test.h"

u_int64_t do_bubblesort( int *sortlist, int asize )
{
	int x = 0, tmpSwap = 0, haveSwapped = 0;
	u_int64_t iter = 0;

	do
	{
		haveSwapped = 0;

		for( x = 0; x < ( asize - 1 ); x++ )
		{
			if( sortlist[ x ] > sortlist[ x + 1 ] )
			{
				//swap
				tmpSwap = sortlist[ x + 1 ];
				sortlist[ x + 1 ] = sortlist[ x ];
				sortlist[ x ] = tmpSwap;
				haveSwapped = 1;
			}
			iter++;
		}
		
	} while( haveSwapped );

	return( iter );
}

