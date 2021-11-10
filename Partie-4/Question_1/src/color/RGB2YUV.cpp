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

#include "ap_fixed.h"
#include "ap_int.h"


void RGB2YUV(const uint8_t din[3], uint8_t dout[3])
{
    ap_fixed<8, 1, AP_RND> R1 = 0.299,   G1 = 0.587,   B1 = 0.114;
    ap_fixed<8, 1, AP_RND> R2 = -0.1687, G2 = -0.3313, B2 = 0.5;
    ap_fixed<8, 1, AP_RND> R3 = 0.5,     G3 = -0.4187, B3 = -0.0813;

    dout[0] = (R1 * din[0] + G1 * din[1] + B1 * din[2]      );
    dout[1] = (R2 * din[0] + G2 * din[1] + B2 * din[2] + 128);
    dout[2] = (R3 * din[0] + G3 * din[1] + B3 * din[2] + 128);

    dout[0] = (dout[0] > 255) ? 255 : dout[0];
    dout[1] = (dout[1] > 255) ? 255 : dout[1];
    dout[2] = (dout[2] > 255) ? 255 : dout[2];

    dout[0] = (dout[0] < 0) ? 0 : dout[0];
    dout[1] = (dout[1] < 0) ? 0 : dout[1];
    dout[2] = (dout[2] < 0) ? 0 : dout[2];
}
