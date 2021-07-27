#include "sort-test.h"

/* Predeclare functions */
void displaySortedList( int *sortedlist, int asize );
void dupRandomArray( int *static_list, int *working_list, int asize );
void runSort( char *sortname, sortFun sortModule, int *staticRandoms, int asize );
void generateStaticRandoms( int srn, int *srnd );
int getLargestSortSize();

/* List of sort types to run */
const SORT sortRunPlan[] =   {
                                { "Small Balanced sort",            20,     0, 20,      0, ST_BALANCED      },
                                { "Medium Balanced sort",           5000,   0, 5000,    0, ST_BALANCED      },
                                { "Large Balanced sort",            50000,  0, 50000,   0, ST_BALANCED      },
                                { "Small Top Weighted sort",        20,     0, 20,      0, ST_TOP_WEIGHT    },
                                { "Medium Top Weighted sort",       5000,   0, 5000,    0, ST_TOP_WEIGHT    },
                                { "Large Top Weighted sort",        50000,  0, 50000,   0, ST_TOP_WEIGHT    },
                                { "Small Bottom Weighted sort",     20,     0, 20,      0, ST_BOT_WEIGHT    },
                                { "Medium Bottom Weighted sort",    5000,   0, 5000,    0, ST_BOT_WEIGHT    },
                                { "Large Bottom Weighted sort",     50000,  0, 50000,   0, ST_BOT_WEIGHT    }
                             };

const uint totalSortRuns = sizeof( sortRunPlan ) / sizeof( struct sort_ref );

int main()
{
    time_t t;
    int staticRandoms[ getLargestSortSize() ];
    uint sortRunNum = 0;
    
    // Init random number generator
    srand( (unsigned) time( &t ) );
       
    while( sortRunNum < totalSortRuns )
    {
        // Generate static randoms to be sorted
        generateStaticRandoms( sortRunNum, &staticRandoms[0] );
            
        printf( "\n--- %d Random numbers generated [%s] ---\n", sortRunPlan[ sortRunNum ].size, sortRunPlan[ sortRunNum ].sortName );

        runSort( "Bubble Sort",     &do_bubblesort,     staticRandoms, sortRunPlan[ sortRunNum ].size );    
        runSort( "Insertion Sort",  &do_insertionsort,  staticRandoms, sortRunPlan[ sortRunNum ].size );
        runSort( "Gnome Sort",      &do_gnomesort,      staticRandoms, sortRunPlan[ sortRunNum ].size );
        runSort( "Quick Sort",      &do_quicksort,      staticRandoms, sortRunPlan[ sortRunNum ].size );
        runSort( "Comb Sort",       &do_combsort,       staticRandoms, sortRunPlan[ sortRunNum ].size );
        runSort( "Tim Sort",        &do_timsort,        staticRandoms, sortRunPlan[ sortRunNum ].size );
        runSort( "Radix Sort",      &do_radixsort,      staticRandoms, sortRunPlan[ sortRunNum ].size );
        
        sortRunNum++;
    }
        
    printf("\nSorting Complete.\n\n");
    
    return( 0 );
}

int getLargestSortSize()
{
    int largestSize, x;
    
    for( largestSize = 0, x = 0; x < totalSortRuns; x++ )
    {
        if( sortRunPlan[ x ].size > largestSize )
            largestSize = sortRunPlan[ x ].size;
    }
    
    return( largestSize );
}

void generateStaticRandoms( int srn, int *srnd )
{
    switch( sortRunPlan[ srn ].sortType ) 
    {
        case ST_BALANCED:
            // Populate balanced array of random numbers
            for ( int x = 0; x < sortRunPlan[ srn ].size; x++ )
            {
                srnd[ x ] = randNumGen( sortRunPlan[ srn ].lowerlimit, sortRunPlan[ srn ].upperlimit);
            }
            break;
            
        case ST_TOP_WEIGHT:
            // Populate top weighted array of random numbers
            for ( int x = 0; x < sortRunPlan[ srn ].size; x++ )
            {
                srnd[ x ] = randNumGen_skewed( sortRunPlan[ srn ].lowerlimit, sortRunPlan[ srn ].upperlimit, 3.0f );
            }
            break;  
            
        case ST_BOT_WEIGHT:
            // Populate bottom weighted array of random numbers
            for ( int x = 0; x < sortRunPlan[ srn ].size; x++ )
            {
                srnd[ x ] = randNumGen_skewed( sortRunPlan[ srn ].lowerlimit, sortRunPlan[ srn ].upperlimit, 0.4f );
            }
            break;  
    }
        
    return;
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

void runSort( char *sortname, sortFun sortModule, int *staticRandoms, int asize )
{
    int workingRandoms[ asize ];
    int msec;
    clock_t start, diff;
    u_int64_t iter;

    printf( "    %16s starting...       ", sortname );
    fflush( stdout );
    dupRandomArray( staticRandoms, workingRandoms, asize );
    start = clock();
    iter = sortModule( workingRandoms, asize );
    diff = clock() - start;
    msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
    printf( "[%20ld iterations]... complete. Time taken:[%8d.%03d] seconds.  Perf:[%.06f]\n", iter, msec/1000, msec%1000, ( (float) asize / (float) iter ) );
    displaySortedList( workingRandoms, asize );
}
