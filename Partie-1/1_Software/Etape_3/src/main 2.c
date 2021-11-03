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

int PGCD2(int N1, int N2)
{
	if (N1 == 0)
		return N2;
	if (N2 == 0)
		return N1;
	
	int temp;
	while(N2 != 0)
	{
		temp = N2;
		N2 = N1 % N2;
		N1 = temp;
	}
	return N1;
}

int RandA()
{
	return rand() % 65536;
}

int RandB()
{
	return rand() % 65536;
}

int main (int argc, char * argv [])
{
	printf("(II) Starting PGCD program\n");
	srand(time(NULL));

	int tests = 65536;
	int i;
	for (i = 0; i < tests; i++)
	{
		int A = RandA();
		int B = RandB();
		if (PGCD(A, B) != PGCD2(A, B))
			printf("Erreur !");
	}
	printf("Nombre de tests réalisés : %d\n", i);
	printf("(II) End of PGCD program\n");
  	
	return 0;
}
