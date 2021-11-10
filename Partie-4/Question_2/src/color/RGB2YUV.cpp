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

using namespace std;

inline int32_t min (int32_t a, int32_t b           ){ return ((a<b)?a:b); }
inline int32_t max (int32_t a, int32_t b           ){ return ((a>b)?a:b); }
inline int32_t clip(int32_t a, int32_t b, int32_t c){ return min(max(a,b),c); }

void RGB2YUV(const uint8_t din[3], uint8_t dout[3])
{
    const int W     = 8;
    const int STEP  = 1;

    const ap_int<W + STEP> R1 = round(0.299    * (1 << W));
    const ap_int<W + STEP> G1 = round(0.587    * (1 << W));
    const ap_int<W + STEP> B1 = round(0.114    * (1 << W));
    const ap_int<W + STEP> R2 = round(-0.1687  * (1 << W));
    const ap_int<W + STEP> G2 = round(-0.3313  * (1 << W));
    const ap_int<W + STEP> B2 = round(0.5      * (1 << W));
    const ap_int<W + STEP> R3 = round(0.5      * (1 << W));
    const ap_int<W + STEP> G3 = round(-0.4187  * (1 << W));
    const ap_int<W + STEP> B3 = round(-0.0813  * (1 << W));

#if 1
    ap_int<8 + 1> Y  =  (R1 * din[0] + G1 * din[1] + B1 * din[2]) >> W;
    ap_int<8 + 1> Cb = ((R2 * din[0] + G2 * din[1] + B2 * din[2]) >> W) + 128;
    ap_int<8 + 1> Cr = ((R3 * din[0] + G3 * din[1] + B3 * din[2]) >> W) + 128;

#else
    ap_int<8 + W + W> Y  =  R1 * din[0] + G1 * din[1] + B1 * din[2];
    ap_int<8 + W + W> Cb =  R2 * din[0] + G2 * din[1] + B2 * din[2];
    ap_int<8 + W + W> Cr =  R3 * din[0] + G3 * din[1] + B3 * din[2];

    ap_int<8 + W + 2> Y1    = Y >> W;
    ap_int<8 + W + 2> Cb1   = (Cb >> W) + 128 ;
    ap_int<8 + W + 2> Cr1   = (Cr >> W) + 128 ;
#endif

    dout[0] = clip(Y,  0, 255);
    dout[1] = clip(Cb, 0, 255);
    dout[2] = clip(Cr, 0, 255);
}