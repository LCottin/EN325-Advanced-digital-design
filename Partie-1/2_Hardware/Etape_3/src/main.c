#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

int PGCD(int A, int B)
{
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
	return A;
}

int RandA()
{
	return rand() % 65536;
}

int RandB()
{
	return rand() % 65536;
}

int main (int argc, char * argv []){
	printf("(II) Starting PGCD program\n");
	srand(time(NULL));

	int valeur = 20000;
	for (int i = 0; i < valeur; i++)
	{
		int A = RandA();
		int B = RandB();
		// printf("Rand A = %d\n", A);
		// printf("Rand B = %d\n", B);
		printf("PGCD(%d, %d) = %d\n", A, B, PGCD(A, B));
	}
	printf("(II) End of PGCD program\n");
  	
	return 0;
}
