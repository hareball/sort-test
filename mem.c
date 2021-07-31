#include "sort-test.h"

/* Use to allocate heap memory for sorts */
char *salloc_mem( size_t size, STATS *sortStats )
{
    char *mem;
    
    mem = malloc( size );
    
    assert( mem > 0 );
    
    sortStats->memoryUsed += size;
    
    return( mem );
}

/* Equivalent of free, use to free memory allocated my salloc memory */
void sfree_mem( char *memptr, STATS *sortStats )
{
    free( memptr );
    return;
}
