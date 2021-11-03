/*
 * Copyright 2020 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "RGB2YUV.hpp"


void RGB2YUV(const int32_t din[3], int32_t dout[3])
{
    dout[0] = (0.299  * din[0] + 0.587  * din[1] + 0.114  * din[2]);
    dout[1] = (-0.1687 * din[0] - 0.3313 * din[1] + 0.5    * din[2] + 128);
    dout[2] = (0.5     * din[0] - 0.4187 * din[1] - 0.0813 * din[2] + 128);

    dout[0] = (dout[0] > 255) ? 255 : dout[0];
    dout[1] = (dout[1] > 255) ? 255 : dout[1];
    dout[2] = (dout[2] > 255) ? 255 : dout[2];

    dout[0] = (dout[0] < 0) ? 0 : dout[0];
    dout[1] = (dout[1] < 0) ? 0 : dout[1];
    dout[2] = (dout[2] < 0) ? 0 : dout[2];
    
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
