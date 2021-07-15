#include "sort-test.h"

/* Predeclare functions */
void displaySortedList( int *sortedlist, int asize );
void dupRandomArray( int *static_list, int *working_list, int asize );
void runSort( char *sortname, sortType sortFunc, int *staticRandoms, int asize );

/* Constants */
const int largeArraySize = 50000;
const int mediumArraySize = 5000;
const int smallArraySize = 20;

int main()
{
	time_t t;
	int staticRandoms[ largeArraySize ];

	// Init random number generator
	srand( (unsigned) time( &t ) );
	
	// Populate small array of random numbers
	for ( int x = 0; x < smallArraySize; x++ )
	{
		staticRandoms[ x ] = rand();
	}
	printf( "\n--- %d Random numbers generated ---\n", smallArraySize );
	runSort( "Bubble Sort", &do_bubblesort, staticRandoms, smallArraySize );
	runSort( "Insertion Sort", &do_insertionsort, staticRandoms, smallArraySize );
	runSort( "Quick Sort", &do_quicksort, staticRandoms, smallArraySize );
	runSort( "Gnome Sort", &do_gnomesort, staticRandoms, smallArraySize );
	runSort( "Comb Sort", &do_combsort, staticRandoms, smallArraySize );

	// Populate medium array of random numbers
	for ( int x = 0; x < mediumArraySize; x++ )
	{
		staticRandoms[ x ] = rand();
	}
	printf( "\n--- %d Random numbers generated ---\n", mediumArraySize );
	runSort( "Bubble Sort", &do_bubblesort, staticRandoms, mediumArraySize );
	runSort( "Insertion Sort", &do_insertionsort, staticRandoms, mediumArraySize );
	runSort( "Quick Sort", &do_quicksort, staticRandoms, mediumArraySize );
	runSort( "Gnome Sort", &do_gnomesort, staticRandoms, mediumArraySize );
	runSort( "Comb Sort", &do_combsort, staticRandoms, mediumArraySize );
	
	// Populate large array of random numbers
	for ( int x = 0; x < largeArraySize; x++ )
	{
		staticRandoms[ x ] = rand();
	}
	printf( "\n--- %d Random numbers generated ---\n", largeArraySize );
	runSort( "Bubble Sort", &do_bubblesort, staticRandoms, largeArraySize );
	runSort( "Insertion Sort", &do_insertionsort, staticRandoms, largeArraySize );
	runSort( "Quick Sort", &do_quicksort, staticRandoms, largeArraySize );
	runSort( "Gnome Sort", &do_gnomesort, staticRandoms, largeArraySize );
	runSort( "Comb Sort", &do_combsort, staticRandoms, largeArraySize );
	
	printf("\nSorting Complete.\n\n");
	
	return( 0 );
}

void displaySortedList( int *sortedlist, int asize )
{
	if( SHOW_SORTED_LIST )
	{
		for( int x = 0; x < asize; x++ )
		{
			if( x < 4 || x > ( asize - 5 ) )
				printf( "[%d] - %d\n", x, sortedlist[ x ] );

			if( x == 5 )
				printf( "....\n" );
		}
		printf( "\n" );
	}

	return;
}

void dupRandomArray( int *static_list, int *working_list, int asize )
{
	for ( int x = 0; x < asize; x++ )
	{
		working_list[ x ] = static_list[ x ];
	}
}

void runSort( char *sortname, sortType sortFunc, int *staticRandoms, int asize )
{
	int workingRandoms[ asize ];
	int msec;
	clock_t start, diff;
	u_int64_t iter;

	printf( "    %16s starting...       ", sortname );
	fflush( stdout );
	dupRandomArray( staticRandoms, workingRandoms, asize );
	start = clock();
	iter = sortFunc( workingRandoms, asize );
	diff = clock() - start;
	msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
	printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.  Perf:[%.06f]\n", iter, msec/1000, msec%1000, (float) ( (float) asize / (float) iter ) );
	displaySortedList( workingRandoms, asize );
}
