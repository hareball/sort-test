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
