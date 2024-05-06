#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_SIZE 10
int main(int argc, char* argv[])
{
	int a[ARRAY_SIZE];
	omp_set_num_threads(4);
	
	////////////// Fill the array ////////////////////
	// Seed the random number generator
	srand(time(NULL));
	int i; //It should declared here not in the for loop
	#pragma omp parallel for
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		a[i] = (rand() % 10) + 1;
	}

	//////////////////Print the array elements ////////////////////////////////
	#pragma omp parallel for ordered
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		#pragma omp ordered
		{
			printf("a[%d] = %d\n", i, a[i]);
		}
	}
	printf("\n");

	////////////////////////////search an element val ////////////////////////////////	
	int val;
	printf("Please fill the value val to be searched \n");
	scanf("%d", &val);

	int found = 0;
	#pragma omp parallel for
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		if(a[i] == val) 
		{
			printf("Found the value at i = %d\n", i);
			found = 1;
		}
	}
	if(found) printf("Value `%d` was found !\n\n", val);
	else printf("Value `%d` was not found !\n\n", val);

	/////////////////////////Number of occurence of val////////////////////////////////
	int occurences = 0;
	#pragma omp parallel for reduction(+ : occurences)
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		if(a[i] == val) occurences++;
	}
	printf("Number of occurences = %d\n\n", occurences);

	/////////////////////////Multiplication of ALL even number in the array////////////
	int productOfEvenNumbers = 1;
	#pragma omp parallel for reduction(* : productOfEvenNumbers)
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		productOfEvenNumbers = 1;
		if(a[i] % 2 == 0) productOfEvenNumbers *= a[i];
	}
	printf("Product of all even numbers = %d\n\n", productOfEvenNumbers);

	//////////////////////////Compare Two Arrays /////////////////////////////////
	int b[ARRAY_SIZE];
	//Fill the array b
	#pragma omp parallel for
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		b[i] = (rand() % 10) + 1;
		printf("Added b[%d] = %d\n", i, b[i]);
	}

	int identical = 1;
	#pragma omp parallel for reduction(& : identical)
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		if(a[i] != b[i]) identical = 0;
	}
	printf("Identical ? => %d\n\n", identical);

	/////////////////////////////// Calculate the average ///////////////////////////
	int sum = 0;
	#pragma omp parallel for reduction(+ : sum)
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		sum += a[i];
	}
	printf("Average = %lf\n\n", (double)sum / ARRAY_SIZE);

	/////////////////////////////// Search the maximum ///////////////////////////
	int Max = a[0];
	#pragma omp parallel for reduction(max : Max)
	for (i = 1; i < ARRAY_SIZE; i++)
	{
		if(a[i] > Max) Max = a[i];
	}
	printf("Max = %d\n\n", Max);

	//////////////////////////////////////////////////////////////////////////

	return 0;
}

