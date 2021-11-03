#include "pgcd.h"


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

