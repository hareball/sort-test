
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

int randNumGen( int min, int max )
{
    return( rand() % ( max - min + 1 ) + min );
}

int randNumGen_skewed( int min, int max, float skew )
{
    float randomf = (float) rand() / (float) RAND_MAX;

    int result = (int) floorf( ( min + ( max + 1 - min ) ) * ( powf( randomf, skew ) ) );
            
    return( result );
}
