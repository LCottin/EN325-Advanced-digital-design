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

#include <iostream>
#include <math.h>

using namespace std;

#define Y   ycbcr[0]
#define Cb  ycbcr[1]
#define Cr  ycbcr[2]

#define R   rvb[0]
#define G   rvb[1]
#define B   rvb[2]

void RGB_2_YCbCr (int rvb[3], int ycbcr[3])
{
    Y  = (0.299   * R + 0.587  * G + 0.114  * B);
    Cb = (-0.1687 * R - 0.3313 * G + 0.5    * B + 128);
    Cr = (0.5     * R - 0.4187 * G - 0.0813 * B + 128);
}

void YCbCr_2_RGB (int ycbcr[3], int rvb[3])
{
    R = Y + 1.402       * (Cr - 128);
    G = Y - 0.344414    * (Cb - 128) - 0.71414 * (Cr - 128);
    R = Y + 1.772       * (Cb - 128);
}

//
// Programme de test des fonctions de conversion
//
int main (int argc, char * argv [])
{
    int rvb[3] = {  0,   0,   0};
    int ycbcr[3]; 
    RGB_2_YCbCr(rvb, ycbcr);
    printf("R = %3d, G = %3d, B = %3d \t Y = %3d, Cb = %3d, Cr = %3d\n", R, G, B, Y, Cb, Cr);

    R = 0;
    G = 0;
    B = 128;
    RGB_2_YCbCr(rvb, ycbcr);
    printf("R = %3d, G = %3d, B = %3d \t Y = %3d, Cb = %3d, Cr = %3d\n", R, G, B, Y, Cb, Cr);

    R = 0;
    G = 128;
    B = 0;
    RGB_2_YCbCr(rvb, ycbcr);
    printf("R = %3d, G = %3d, B = %3d \t Y = %3d, Cb = %3d, Cr = %3d\n", R, G, B, Y, Cb, Cr);

    R = 128;
    G = 0;
    B = 0;
    RGB_2_YCbCr(rvb, ycbcr);
    printf("R = %3d, G = %3d, B = %3d \t Y = %3d, Cb = %3d, Cr = %3d\n", R, G, B, Y, Cb, Cr);
	return 0;
}
