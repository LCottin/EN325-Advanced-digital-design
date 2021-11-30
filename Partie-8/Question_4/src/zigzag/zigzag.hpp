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
#ifndef _ZIGZAG_
#define _ZIGZAG_


#include <cstdio>
#include <cstdlib>
#include <cstdint>


const uint8_t _zz_[64] = {
    0,  1,  8, 16,  9,  2,  3,  10,
    17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63
};


void zigzag(const int16_t din[64], int16_t dout[64])
{
#pragma HLS INLINE off
    for(int32_t k = 0; k < 64; k += 1)
    {
        dout[k] = din[ _zz_[k] ];
    }
}


void zigzag_full(const int16_t din[64], int16_t dout[64])
{
#pragma HLS INLINE off
    for(int32_t k = 0; k < 192; k += 64)
    {
        zigzag(din + k, dout + k);
    }
}


#endif
