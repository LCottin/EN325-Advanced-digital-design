#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <getopt.h>
#include <iostream>

#include "./color/RGB2YUV.hpp"
#include "./color/YUV2RGB.hpp"

void store_in_binary(FILE* f, int n)
{
	int i;
	for(i = 0; i < 24; i += 1)
	{
		int bit = (n >> (23 - i)) & 0x01;
		fprintf(f, "%d", bit);
	}
	fprintf(f, "\n");
}

//
// Generation des valeurs dans l'intervalle [1, 255]
// Sinon cela va etre compliqué en VHDL !
//
int RANDV( )
{
	return (rand() % 254) + 1;
}

int main (int argc, char * argv []){

	FILE *fA = fopen("data_in.txt", "w");
	if (fA == NULL)
	{
		printf("Impossible d'ouvrir le fichier data_a.txt en mode écriture\n");
		exit(1);
	}

	FILE *fB = fopen("yuv_cpp.txt", "w");
	if (fB == NULL)
	{
		printf("Impossible d'ouvrir le fichier data_a.txt en mode écriture\n");
		exit(1);
	}

	int i;
	for(i = 0; i < 100; i += 1)
	{
		int A, B;
    uint8_t RGB[3], YUV[3];

    A = (RANDV() << 16) + (RANDV() << 8) + RANDV();

    RGB[0] = (A & 0xFF0000) >> 16;
    RGB[1] = (A & 0xFF00) >> 8;
    RGB[2] = (A & 0xFF);

    RGB2YUV(RGB, YUV);

    B = (YUV[0] << 16) + (YUV[1] << 8) + YUV[2];

		store_in_binary(fA, A);
		store_in_binary(fB, B);
	}

	fclose( fA );
	fclose( fB );

  return 0;
}
