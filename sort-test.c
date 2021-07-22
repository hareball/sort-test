#include "sort-test.h"

/* Predeclare functions */
void displaySortedList( int *sortedlist, int asize );
void dupRandomArray( int *static_list, int *working_list, int asize );
void runSort( char *sortname, sortType sortFunc, int *staticRandoms, int asize );

/* Constants */
const int largeSize = 50000;

/* Largest sort to be defined last */
const SORT sortRunPlan[] =   {
								{20, 0},			// Small sort
								{5000, 0},			// Medium sort
								{50000, 0}			// Large sort
							 };

const int totalSortRuns = sizeof(sortRunPlan) / (sizeof(int)*2);	

int main()
{
	time_t t;
	int staticRandoms[ sortRunPlan[ totalSortRuns - 1 ].size ];
	int sortRunNum;
	
	// Init random number generator
	srand( (unsigned) time( &t ) );
	
	sortRunNum = 0;
	
	while( sortRunNum < totalSortRuns )
	{
		// Populate array of random numbers
		for ( int x = 0; x < sortRunPlan[ sortRunNum ].size; x++ )
		{
			staticRandoms[ x ] = rand();
		}
		
		printf( "\n--- %d Random numbers generated ---\n", sortRunPlan[ sortRunNum ].size );

		runSort( "Bubble Sort", &do_bubblesort, staticRandoms, sortRunPlan[ sortRunNum ].size );	
		runSort( "Insertion Sort", &do_insertionsort, staticRandoms, sortRunPlan[ sortRunNum ].size );
		runSort( "Gnome Sort", &do_gnomesort, staticRandoms, sortRunPlan[ sortRunNum ].size );
		runSort( "Quick Sort", &do_quicksort, staticRandoms, sortRunPlan[ sortRunNum ].size );
		runSort( "Comb Sort", &do_combsort, staticRandoms, sortRunPlan[ sortRunNum ].size );
		runSort( "Tim Sort", &do_timsort, staticRandoms, sortRunPlan[ sortRunNum ].size );
		
		sortRunNum++;
	}
		
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
