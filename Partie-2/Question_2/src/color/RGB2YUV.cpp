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

#include "RGB2YUV.hpp"


void RGB2YUV(const int32_t din[3], int32_t dout[3])
{
    dout[0]  = (0.299  * din[0] + 0.587  * din[1] + 0.114  * din[2]);
    dout[1] = (-0.1687 * din[0] - 0.3313 * din[1] + 0.5    * din[2] + 128);
    dout[2] = (0.5     * din[0] - 0.4187 * din[1] - 0.0813 * din[2] + 128);
}

void RGB2YUV(const uint8_t din[192], int32_t dout[192])
{
    int32_t conv[3];
    for(int32_t k = 0; k < 192; k += 3)
    {
        for(int i = 0; i < 3; i++)  // Conversion des donnees de type uint8_t
            conv[i] = din[k+i];     // en données de type int32_t

        RGB2YUV(conv, dout + k);
    }
}
