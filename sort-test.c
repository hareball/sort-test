#include "sort-test.h"

/* Predeclare functions */
void displaySortedList( int *sortedlist );
void dupRandomArray( int *static_list, int *working_list );
void runSort( char *sortname, sortType sortFunc, int *staticRandoms );

int main()
{
	time_t t;
	int staticRandoms[ ARRAYSIZE ];

	// Init random number generator
	srand( (unsigned) time( &t ) );

	// Populate array of random numbers
	for ( int x = 0; x < ARRAYSIZE; x++ )
	{
		staticRandoms[ x ] = rand();
	}

	printf( "*** %d Random numbers generated.\n", ARRAYSIZE );

	runSort( "Bubble Sort", &do_bubblesort, staticRandoms );
	runSort( "Insertion Sort", &do_insertionsort, staticRandoms );
	runSort( "Quick Sort", &do_quicksort, staticRandoms );
	runSort( "Gnome Sort", &do_gnomesort, staticRandoms );
	runSort( "Comb Sort", &do_combsort, staticRandoms );

	return( 0 );
}

void displaySortedList( int *sortedlist )
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
		printf( "\n" );
	}

	return;
}

void dupRandomArray( int *static_list, int *working_list )
{
        for ( int x = 0; x < ARRAYSIZE; x++ )
        {
                working_list[ x ] = static_list[ x ];
	}
}

void runSort( char *sortname, sortType sortFunc, int *staticRandoms )
{
	int workingRandoms[ ARRAYSIZE ];
        int msec;
        clock_t start, diff;
        u_int64_t iter;

        printf( "*** %s starting...\t\t", sortname );
        fflush( stdout );
        dupRandomArray( staticRandoms, workingRandoms );
        start = clock();
	iter = sortFunc( workingRandoms );
        diff = clock() - start;
        msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
        printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.\n", iter, msec/1000, msec%1000 );
        displaySortedList( workingRandoms );
}
