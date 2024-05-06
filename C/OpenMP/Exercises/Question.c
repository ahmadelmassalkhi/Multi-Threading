#include <stdio.h>

int main(int argc, char *argv[])
{
	const int ARRAY_SIZE = 5;
	int a[ARRAY_SIZE];
	omp_set_num_threads(4);
	////////////// Fill the array ////////////////////
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
	}
	////////////////////////////search an element val ////////////////////////////////
	int val;
	printf("Please fill the value val to be searched \n");
	scanf("%d", &val);

	int i;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
	}

	/////////////////////////Number of occurence of val////////////////////////////////

	for (i = 0; i < ARRAY_SIZE; i++)
	{
	}

	/////////////////////////Multiplication of ALL even number in the array////////////

	for (i = 0; i < ARRAY_SIZE; i++)
	{
	}

	//////////////////////////Compare Two Arrays /////////////////////////////////

	int b[ARRAY_SIZE];
	// Fill the array b
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
	}

	for (i = 0; i < ARRAY_SIZE; i++)
	{
	}
	/////////////////////////////// Calculate the average ///////////////////////////

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
	}

	/////////////////////////////// Search the maximum ///////////////////////////

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
	}

	//////////////////Print the array elements ////////////////////////////////
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		printf("a[%d] = %2d\n", i, a[i]);
	}

	//////////////////////////////////////////////////////////////////////////

	return 0;
}
