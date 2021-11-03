#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "assert.h"
#include "pgcd.h"

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

	//tests avec 1 ==> 1
	assert(PGCD(1, 2) == 1);
	assert(PGCD(2, 1) == 1);

	//tests avec 0 ==> 10
	assert(PGCD(0, 10) == 10);
	assert(PGCD(10, 0) == 10);

	//tests classiques ==> 8
	assert(PGCD(24, 40)== 8);
	assert(PGCD(40, 24)== 8);

	//tests 2 nombres premiers ==> 1
	assert(PGCD(3, 7) == 1);
	assert(PGCD(7, 3) == 1);

	//tests 2 nombres premiers entre eux ==> 1
	assert(PGCD(3, 4) == 1);
	assert(PGCD(4, 3) == 1);

	printf("(II) End of PGCD program\n");
  	
	return 0;
}
