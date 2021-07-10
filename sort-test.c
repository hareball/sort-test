#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort-test.h"

/* Predeclare functions */
void do_displaysortedlist( int *sortedlist );

int main()
{
	int msec;
	time_t t;
	int randnums[ ARRAYSIZE ], bsrandnums[ ARRAYSIZE ],
	    israndnums[ ARRAYSIZE ], qsrandnums[ ARRAYSIZE ],
	    gsrandnums[ ARRAYSIZE ];
	clock_t start, diff;
	u_int64_t iter;

	// Init random number generator
	srand( (unsigned) time( &t ) );

	for ( int x = 0; x < ARRAYSIZE; x++ )
	{
		randnums[x] = rand();
		bsrandnums[x] = randnums[x];
		israndnums[x] = randnums[x];
		qsrandnums[x] = randnums[x];
		gsrandnums[x] = randnums[x];
	}

	printf( "*** %d Random numbers generated.\n", ARRAYSIZE );

	printf( "*** Bubble Sort starting...\t\t" );
	fflush( stdout );

	start = clock();
	iter = do_bubblesort( bsrandnums );
	diff = clock() - start;

	msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
	printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.\n", iter, msec/1000, msec%1000 );
	do_displaysortedlist( bsrandnums );


	printf( "*** Insertion Sort starting...\t\t" );
	fflush( stdout );

	start = clock();
	iter = do_insertionsort( israndnums );
	diff = clock() - start;

	msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
	printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.\n", iter, msec/1000, msec%1000 );
	do_displaysortedlist( israndnums );

	printf( "*** Quick Sort starting...\t\t" );
	fflush( stdout );

	start = clock();
	iter = do_quicksort( qsrandnums );
	diff = clock() - start;

	msec = ( diff * 1000.0 ) / CLOCKS_PER_SEC;
	printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.\n", iter, msec/1000, msec%1000 );
	do_displaysortedlist( qsrandnums );

        printf( "*** Gnome Sort starting...\t\t" );
        fflush( stdout );

        start = clock();
	iter = do_gnomesort( gsrandnums );
        diff = clock() - start;

        msec = ( diff * 1000.0 ) / CLOCKS_PER_SEC;
	printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.\n", iter, msec/1000, msec%1000 );
        do_displaysortedlist( gsrandnums );

	return( 0 );
}

void do_displaysortedlist( int *sortedlist )
{
	if( SHOW_SORTED_LIST )
	{
		for( int x = 0; x < ARRAYSIZE; x++ )
		{
			if( x < 4 || x > ( ARRAYSIZE - 5 ) )
				printf( "[%d] - %d\n", x, sortedlist[ x ] );

			if( x == 5 )
				printf( "....\n" );
		}
	}

	return;
}
