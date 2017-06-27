#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 	50000

/* Predeclare functions */
void do_displaysortedlist(int *sortedlist);
void do_bubblesort(int *sortlist);
void do_insertionsort(int *sortlist);
void do_quicksort(int *sortlist, int elements);

int main()
{
	int msec;
	time_t t;
	int randnums[ARRAYSIZE], bsrandnums[ARRAYSIZE], israndnums[ARRAYSIZE], qsrandnums[ARRAYSIZE];
	clock_t start, diff;

	/* Init random number generator */
	srand((unsigned) time(&t));

	for (int x = 0; x < ARRAYSIZE; x++)
	{
		randnums[x] = rand();
		bsrandnums[x] = randnums[x];
		israndnums[x] = randnums[x];
		qsrandnums[x] = randnums[x];
	}

	printf("*** %d Random numbers generated.\n\r", ARRAYSIZE);


	printf("*** Bubble Sort starting... ");
	fflush(stdout);

	start = clock();
	do_bubblesort(bsrandnums);
	diff = clock() - start;

	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("complete. Time taken:[%d.%03d] seconds.\n\r", msec/1000, msec%1000);
	do_displaysortedlist(bsrandnums);
	

	printf("\n\r*** Insertion Sort starting... ");
	fflush(stdout);

	start = clock();
	do_insertionsort(israndnums);
	diff = clock() - start;
	
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("complete. Time taken:[%d.%03d] seconds.\n\r", msec/1000, msec%1000);
	do_displaysortedlist(israndnums);



	printf("\n\r*** Quick Sort starting... ");
	fflush(stdout);

	start = clock();
	do_quicksort(qsrandnums, ARRAYSIZE);
	diff = clock() - start;
	
	msec = (diff * 1000.0) / CLOCKS_PER_SEC;
	printf("complete. Time taken:[%d.%03d] seconds.\n\r", msec/1000, msec%1000);
	do_displaysortedlist(qsrandnums);

	return (0);
}

void do_displaysortedlist(int *sortedlist)
{
	for (int x = 0; x < ARRAYSIZE; x++)
	{
		if( x < 4 || x > (ARRAYSIZE - 5))
			printf("[%d] - %d\n\r", x, sortedlist[x]);
		
		if( x == 5 )
			printf("....\n\r");
	}

	return;
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
	int x = 0, tmpSwap = 0;
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


void do_quicksort(int *sortlist, int elements)
{

	#define  MAX_LEVELS  1000

	int  piv, beg[MAX_LEVELS], end[MAX_LEVELS], i=0, L, R;

	long int iter = 0;

	beg[0]=0; end[0]=elements;

	while (i>=0) 
	{
		L=beg[i]; R=end[i]-1;
		if (L<R) 
		{
			piv=sortlist[L]; 
			if (i==MAX_LEVELS-1) 
			{
				return;
			}

		  	while (L<R) 
			{
				while (sortlist[R]>=piv && L<R) 
				{				
					R--;
					iter++;
				}
				if (L<R)
				{
					sortlist[L++]=sortlist[R];
				}
				while (sortlist[L]<=piv && L<R) 
				{
					L++;
					iter++;
				}
				if (L<R) 
				{
					sortlist[R--]=sortlist[L];
				}
			}
		  	sortlist[L]=piv; 
			beg[i+1]=L+1; 
			end[i+1]=end[i]; 
			end[i++]=L; 
		}
		else 
		{
			i--;
			iter++;
		}
	}

	printf("[%ld iterations]... ", iter);

	return; 
}
