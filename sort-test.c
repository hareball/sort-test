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

	printf( "*** Bubble Sort starting... " );
	fflush( stdout );

	start = clock();
	do_bubblesort( bsrandnums );
	diff = clock() - start;

	msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
	printf( "complete. Time taken:[%d.%03d] seconds.\n", msec/1000, msec%1000 );
	do_displaysortedlist( bsrandnums );

	printf( "\n*** Insertion Sort starting... " );
	fflush( stdout );

	start = clock();
	do_insertionsort( israndnums );
	diff = clock() - start;

	msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
	printf( "complete. Time taken:[%d.%03d] seconds.\n", msec/1000, msec%1000 );
	do_displaysortedlist( israndnums );

	printf( "\n*** Quick Sort starting... " );
	fflush( stdout );

	start = clock();
	do_quicksort( qsrandnums );
	diff = clock() - start;

	msec = ( diff * 1000.0 ) / CLOCKS_PER_SEC;
	printf( "complete. Time taken:[%d.%03d] seconds.\n", msec/1000, msec%1000 );
	do_displaysortedlist( qsrandnums );

        printf( "\n*** Gnome Sort starting... " );
        fflush( stdout );

        start = clock();
        do_gnomesort( gsrandnums );
        diff = clock() - start;

        msec = ( diff * 1000.0 ) / CLOCKS_PER_SEC;
        printf( "complete. Time taken:[%d.%03d] seconds.\n", msec/1000, msec%1000 );
        do_displaysortedlist( gsrandnums );

	return( 0 );
}

void do_displaysortedlist( int *sortedlist )
{
	for( int x = 0; x < ARRAYSIZE; x++ )
	{
		if( x < 4 || x > ( ARRAYSIZE - 5 ) )
			printf( "[%d] - %d\n", x, sortedlist[ x ] );

		if( x == 5 )
			printf( "....\n" );
	}

	return;
}
