#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 	50000

// predeclare functions
void do_bubblesort(int *sortlist);
void do_insertionsort(int *sortlist);

int main()
{
	int i, n, msec;
	time_t t;
	int randnums[ARRAYSIZE], bsrandnums[ARRAYSIZE], israndnums[ARRAYSIZE];
	clock_t start, diff;

	n = 5;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

	for (int x = 0; x < ARRAYSIZE; x++)
	{
		randnums[x] = rand();
		bsrandnums[x] = randnums[x];
		israndnums[x] = randnums[x];
	}

	printf("*** %d Random numbers generated.\n\r", ARRAYSIZE);

	printf("*** Bubble Sort starting... ");

	fflush(stdout);


	start = clock();
	do_bubblesort(bsrandnums);
	diff = clock() - start;

	msec = diff * 1000 / CLOCKS_PER_SEC;


	printf("complete. Time taken:[%d.%d] seconds.\n\r", msec/1000, msec%1000);

	for (int x = 0; x < ARRAYSIZE; x++)
	{
		if( x< 4 || x >(ARRAYSIZE - 4))
			printf("[%d] - %d\n\r", x, bsrandnums[x]);
		
		if( x==5 )
			printf("....\n\r");
	}
	
	printf("\n\r*** Insertion Sort starting... ");

	fflush(stdout);

	start = clock();
	do_insertionsort(israndnums);
	diff = clock() - start;
	
	msec = diff * 1000 / CLOCKS_PER_SEC;
	
	printf("complete. Time taken:[%d.%d] seconds.\n\r", msec/1000, msec%1000);
	
	for (int x = 0; x < ARRAYSIZE; x++)
	{
		if( x< 4 || x >(ARRAYSIZE - 4))
			printf("[%d] - %d\n\r", x, israndnums[x]);
		
		if( x==5 )
			printf("....\n\r");
	}

	return (0);
}

void do_bubblesort(int *sortlist)
{
	int x = 0, tmpSwap = 0;
	long int iter = 0;

	do
	{
		tmpSwap = 0;
		
		for( x=0; x<(ARRAYSIZE-1); x++ )
		{
			if( sortlist[x] > sortlist[x+1])
			{
				//swap
				tmpSwap = sortlist[x+1];
				sortlist[x+1] = sortlist[x];
				sortlist[x] = tmpSwap;
			}
			iter++;
		}
		
	} while (tmpSwap);

	printf("[%ld iterations]... ", iter);
	
	return;
}

void do_insertionsort(int *sortlist)
{
	int x = 0, tmpSwap = 0, cpos = 0;
	long int iter = 0;
	
	for( x=1; x<(ARRAYSIZE); x++ )
	{
		int cpos = x;
		
		// take it to the top
		do
		{	
			if( sortlist[cpos] < sortlist[cpos-1] )
			{
				//swap them
				tmpSwap = sortlist[cpos-1];
				sortlist[cpos-1] = sortlist[cpos];
				sortlist[cpos] = tmpSwap;
			}
			
			cpos--;
			
			iter++;
			
		} while (sortlist[cpos] < sortlist[cpos-1] &&
				cpos > 0 );
	}
	
	printf("[%ld iterations]... ", iter);
	
	return;
}

