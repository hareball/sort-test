
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

/* For recursive functions, if we need to show stack memory used -- does not allocate any memory */
void sadd_stackmem( size_t size, STATS *sortStats )
{
    sortStats->memoryUsed += size;
    return;
}
