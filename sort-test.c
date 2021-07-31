#include "sort-test.h"

/* Predeclare functions */
void displaySortedList( int *sortedlist, uint32_t asize );
void dupRandomArray( int *static_list, int *working_list, uint32_t asize );
void runSort( int algorithmNum, int *staticRandoms, uint32_t asize );
void generateStaticRandoms( int srn, int *srnd );
uint32_t getLargestSortSize();

int main()
{
    time_t t;
    int *staticRandoms;
    uint sortRunNum = 0;
    uint sortNumber;
    
    // Init random number generator
    srand( (unsigned) time( &t ) );
    
    // Allocate heap for static randoms
    staticRandoms = malloc( sizeof(int) * getLargestSortSize() );
       
    while( sortRunNum < totalSortRuns )
    {
        // Generate static randoms to be sorted
        generateStaticRandoms( sortRunNum, &staticRandoms[0] );
            
        printf( "\n--- %d Random numbers generated [%s] ---\n", sortRunPlan[ sortRunNum ].size, sortRunPlan[ sortRunNum ].sortName );

        for( sortNumber = 0; sortNumber < totalSortAlgorithms; sortNumber++ )
        {
            if( sortRunPlan[ sortRunNum ].isLarge && sortAlgorithms[ sortNumber ].runLarge )
                runSort( sortNumber, staticRandoms, sortRunPlan[ sortRunNum ].size );
            else
            {
                if( !sortRunPlan[ sortRunNum ].isLarge )
                {
                    runSort( sortNumber, staticRandoms, sortRunPlan[ sortRunNum ].size );
                }
            } 
        }   

        sortRunNum++;
    }
    
    free( staticRandoms );
        
    printf("\nSorting Complete.\n\n");
    
    return( 0 );
}

uint32_t getLargestSortSize()
{
    uint32_t largestSize, x;
    
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
            for ( uint32_t x = 0; x < sortRunPlan[ srn ].size; x++ )
            {
                srnd[ x ] = randNumGen( sortRunPlan[ srn ].lowerlimit, sortRunPlan[ srn ].upperlimit);
            }
            break;
            
        case ST_TOP_WEIGHT:
            // Populate top weighted array of random numbers
            for ( uint32_t x = 0; x < sortRunPlan[ srn ].size; x++ )
            {
                srnd[ x ] = randNumGen_skewed( sortRunPlan[ srn ].lowerlimit, sortRunPlan[ srn ].upperlimit, 3.0f );
            }
            break;  
            
        case ST_BOT_WEIGHT:
            // Populate bottom weighted array of random numbers
            for ( uint32_t x = 0; x < sortRunPlan[ srn ].size; x++ )
            {
                srnd[ x ] = randNumGen_skewed( sortRunPlan[ srn ].lowerlimit, sortRunPlan[ srn ].upperlimit, 0.4f );
            }
            break;  
    }
        
    return;
}

void displaySortedList( int *sortedlist, uint32_t asize )
{
    if( SHOW_SORTED_LIST )
    {
        for( uint32_t x = 0; x < asize; x++ )
        {
            if( x < 4 || x > ( asize - 5 ) )
                printf( "[%d] - %d\n", x, sortedlist[ x ] );
    
            if( x == (uint32_t) ( asize / 2 ) )
                printf( "[%d] - %d\n", x, sortedlist[ x ] );

            if( x == 5 )
                printf( "....\n" );
                
            if( x == (uint32_t) ( asize / 2 ) + 1 )
                printf( "....\n" );
        }
        printf( "\n" );
    }

    return;
}

void dupRandomArray( int *static_list, int *working_list, uint32_t asize )
{
    for ( uint32_t x = 0; x < asize; x++ )
    {
        working_list[ x ] = static_list[ x ];
    }
}

void runSort( int algorithmNum, int *staticRandoms, uint32_t asize )
{
    int *workingRandoms;
    int msec;
    clock_t start, diff;
    STATS sortStats;
    sortFun sortModule = sortAlgorithms[ algorithmNum ].sortModule;
    int confirmedSorted;

    printf( "    %16s starting...       ", sortAlgorithms[ algorithmNum ].algorithmName );
    fflush( stdout );
    
    // Allocate heap for working randoms
    workingRandoms = malloc( sizeof(int) * asize );
    
    // Duplicate static random array into working array (heap alloc)
    dupRandomArray( staticRandoms, workingRandoms, asize );
    
    // Init algorithm stat counters before we use it
    sortStats.iter = 0;
    sortStats.memoryUsed = 0;
    sortStats.memAlloc = &salloc_mem;
    sortStats.memFree = &sfree_mem;

    start = clock();    
    sortModule( workingRandoms, asize, &sortStats );
    diff = clock() - start;
    msec = ( diff * 1000 ) / CLOCKS_PER_SEC;
    
    confirmedSorted = TRUE;
    
    // Lets confirm results have been sorted
    for( uint32_t x = 1; x < asize; x++ )
    {
        if( workingRandoms[ x ] < workingRandoms[ x - 1 ] )
        {
            confirmedSorted = FALSE;
            if( SHOW_ISSUES )
            {
                printf("\nProblem at position:[%d]: [%d], which is smaller than the previous value at position:[%d]: [%d].\n", x, workingRandoms[ x ], x - 1, workingRandoms[ x - 1 ] );
            }
        }
    }
    printf( "[%16ld iterations]... complete. Time taken:[%8d.%03d] seconds.  Perf:[%.06f]  Mem Used:[%12ld] Bytes  Sorted:[%3s]\n", sortStats.iter, msec/1000, msec%1000, ( (float) asize / (float) sortStats.iter ), sortStats.memoryUsed, confirmedSorted ? "YES" : "NO" );
    displaySortedList( workingRandoms, asize );
    
    free( workingRandoms );
}
