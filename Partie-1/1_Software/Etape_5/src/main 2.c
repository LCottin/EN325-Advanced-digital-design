#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "assert.h"

#define MAX_RAND 65536

int PGCD(int A, int B)
{
	int A1 = A;
	int B1 = B;

	/**
	 * Pré-conditions
	 */
	assert(A >= 0);
	assert(B >= 0);
	assert(A < MAX_RAND);
	assert(B < MAX_RAND);

	/**
	 * Algorithme
	 */
	if (A == 0)
		return B;
	if (B == 0)
		return A;
	while (A != B)
	{
		if (A > B)
			A = A - B;
		else 
			B = B - A;
	}

	/**
	 * Post-conditions
	 */
	assert(A <= A1);
	assert(A <= B1);
	assert(A >= 0);

	return A;
}

int RandA()
{
	return rand() % MAX_RAND;
}

int RandB()
{
	return rand() % MAX_RAND;
}

int main (int argc, char * argv []){
	printf("(II) Starting PGCD program\n");
	srand(time(NULL));

	// int valeur = 2000;
	// for (int i = 0; i < valeur; i++)
	// {
	// 	int A = RandA();
	// 	int B = RandB();
	//  printf("Rand A = %d\n", A);
	//  printf("Rand B = %d\n", B);
	// }
	
	printf("PGCD(%d, %d) = %d\n", atoi(argv[1]), atoi(argv[2]), PGCD(atoi(argv[1]), atoi(argv[2])));
	printf("(II) End of PGCD program\n");
  	
	return 0;
}
