
/*
 * sort-test
 * 
 * Copyright (C) 2021 Dan Hare
 *
 * This file is part of sort-test, a free suite of sort algorithms
 *
 * sort-test is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version
 *
 * sort-test is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
 
#include "sort-test.h"

/* Predeclare functions */
void displaySortedList( int *sortedlist, uint32_t asize );
void dupRandomArray( int *static_list, int *working_list, uint32_t asize );
void runSort( int algorithmNum, int *staticRandoms, uint sortRunNum );
void generateStaticRandoms( int srn, int *srnd );

uint32_t getLargestSortSize();


int main()
{
    time_t t;
    int *staticRandoms;
    uint sortRunNum = 0;
    uint sortAlgoNumber;
    
    // Init random number generator
    srand( (unsigned) time( &t ) );
    
    // Allocate heap for static randoms
    staticRandoms = malloc( sizeof( int ) * getLargestSortSize() );
       
    while( sortRunNum < totalSortRuns )
    {
        if( sortRunPlan[ sortRunNum ].active )
        {
            // Generate static randoms to be sorted
            generateStaticRandoms( sortRunNum, &staticRandoms[0] );
                
            write_log( "\n@r--- @w%d Random numbers generated @y[@m%s@y] @r---@w\n", sortRunPlan[ sortRunNum ].size, 
                                                                    sortRunPlan[ sortRunNum ].sortName );


            for( sortAlgoNumber = 0; sortAlgoNumber < totalSortAlgorithms; sortAlgoNumber++ )
            {
                runSort( sortAlgoNumber, staticRandoms, sortRunNum );
            }
        }
        else
        {
           write_log( "\n@r--- @wNot active, skipping @y[@m%s@y] @r---@w\n", sortRunPlan[ sortRunNum ].sortName );
        }

        sortRunNum++;
    }
    
    free( staticRandoms );
        
    write_log("\nSorting Complete.\n\n");
    
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

void swap( int *xp, int *yp )
{
    static int temp;
    
    temp = *xp;
    *xp = *yp;
    *yp = temp;
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
                write_log( "[%d] - %d\n", x, sortedlist[ x ] );
    
            if( x == (uint32_t) ( asize / 2 ) )
                write_log( "[%d] - %d\n", x, sortedlist[ x ] );

            if( x == 5 )
                write_log( "....\n" );
                
            if( x == (uint32_t) ( asize / 2 ) + 1 )
                write_log( "....\n" );
        }
        write_log( "\n" );
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

void runSort( int algorithmNum, int *staticRandoms, uint sortRunNum )
{
    int *workingRandoms;
    int msec, hugePlanSort, confirmedSorted;
    clock_t start, diff;
    STATS sortStats;
    sortFun sortModule = sortAlgorithms[ algorithmNum ].sortModule;
    uint32_t asize;
    char reason[ MAX_STRING_SIZE ], buff[ MAX_STRING_SIZE ];
    

    asize = sortRunPlan[ sortRunNum ].size;
    hugePlanSort = sortRunPlan[ sortRunNum ].isHuge && !sortAlgorithms[ algorithmNum ].runHuge;
    
    if( !sortAlgorithms[ algorithmNum ].active || 
        ( hugePlanSort ) )
    {
        if( ( SHOW_DEACTIVE_HUGE && hugePlanSort ) ||
            ( SHOW_DEACTIVE_NORM && !hugePlanSort ) )
        {
            if( hugePlanSort )
                sprintf( reason, "%s", "does not run for huge sorts" );
            else
                sprintf( reason, "%s", "deactivated" );
                
            write_log( "    @b%22s@w @r--- @wnot running @y(@w%s@y) @r---@w\n", sortAlgorithms[ algorithmNum ].algorithmName, reason );
            fflush( stdout );
        }
        
        return;
    }
   
    write_log( "    @b%22s @wstarting...       ", sortAlgorithms[ algorithmNum ].algorithmName );
    fflush( stdout );
    
    // Allocate heap for working randoms
    workingRandoms = malloc( sizeof( int ) * asize );
    
    // Duplicate static random array into working array (heap alloc)
    dupRandomArray( staticRandoms, workingRandoms, asize );
    
    // Init algorithm stat counters before we use it
    sortStats.iter = 0;
    sortStats.memoryUsed = 0;
    sortStats.memAlloc = &salloc_mem;
    sortStats.memFree = &sfree_mem;
    sortStats.addStackMem = &sadd_stackmem;
    
    // Lets run the sort module
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
                write_log("\nProblem at position:[%d]: [%d], which is smaller than the previous value at position:[%d]: [%d].\n", 
                          x, workingRandoms[ x ], x - 1, workingRandoms[ x - 1 ] );
            }
        }
    }
    sprintf( buff, "@y[@c%16ld@y]@w iterations... complete. Time taken:@y[@c%8d.%03d@y]@w seconds.  Perf:@y[@c%.06f@y]@w  Mem Used:@y[@c%12ld@y]@w Bytes  Sorted:@y[%3s@y]@w\n", 
             sortStats.iter, msec/1000, msec%1000, ( (float) asize / (float) sortStats.iter ), 
             sortStats.memoryUsed, confirmedSorted ? "@gYES" : "@rNO" );
    write_log( buff );
    displaySortedList( workingRandoms, asize );
    
    free( workingRandoms );
}

void write_log( char *fmt, ... )
{
    va_list args;
    
    char dst[ MAX_STRING_SIZE ];

    va_start( args, fmt );
        
    add_colour( dst, fmt );

    vprintf( dst, args );
    va_end( args );

    fflush( stdout );
}
