#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "assert.h"
#include "pgcd.h"


int main (int argc, char * argv []){
	printf("(II) Starting PGCD program\n");
	
	const int taille = 65535;
	int A[taille];
	int B[taille];
	int C[taille];

	FILE* fileA = fopen("./src/Ref_A.txt", "r");
	FILE* fileB = fopen("./src/Ref_B.txt", "r");
	FILE* fileC = fopen("./src/Res_C.txt", "w");

	if (fileA == NULL)
	{
		printf("Erreur d'ouverture A");
		return 0;
	}
	if (fileB == NULL)
	{
		printf("Erreur d'ouverture B");
		return 0;
	}
	if (fileC == NULL)
	{
		printf("Erreur d'ouverture C");
		return 0;
	}

	for (int i = 0; i < taille; i++)
	{
		fscanf(fileA, "%d", &A[i]);
		fscanf(fileB, "%d", &B[i]);
		
		C[i] = PGCD(A[i], B[i]);
		fprintf(fileC, "%d\n", C[i]);
	}
	

	fclose(fileA);
	fclose(fileB);
	fclose(fileC);
	printf("(II) End of PGCD program\n");
  	
	return 0;
}
