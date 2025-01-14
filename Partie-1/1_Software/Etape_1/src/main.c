/*
 * EN325-Advanced-digital-design teaching lab.
 * 
 * Copyright (C) { 2021 }  { Bertrand LE GAL} { Bordeaux-INP }
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int PGCD(int A, int B)
{
	while (A != B)
	{
		if (A > B)
			A = A - B;
		else 
			B = B - A;
	}
	return A;
}

int main (int argc, char * argv []){
	printf("(II) Starting PGCD program\n");

	printf("PGCD(%d, %d) = %d\n", atoi(argv[1]), atoi(argv[2]), PGCD(atoi(argv[1]), atoi(argv[2])));

	printf("(II) End of PGCD program\n");
  return 0;
}
