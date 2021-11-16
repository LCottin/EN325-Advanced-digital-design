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
#define SIZE 6
#define SIZEMIN 8

#include "RGB2YUV.hpp"

#include "ap_fixed.h"
#include "ap_int.h"

using namespace std;

void RGB2YUV(const uint8_t din[3], uint8_t dout[3])
{
  ap_int<SIZE+1> coeff1  =  (  0.299  * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff2  =  (  0.587  * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff3  =  (  0.114  * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff4  =  ( -0.1687 * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff5  =  ( -0.3313 * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff6  =  ( -0.4187 * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff7  =  ( -0.0813 * ( 1 << SIZE ));
  ap_int<SIZE+1> coeff8  =  (  0.5    * ( 1 << SIZE ));

  ap_int<SIZE+1+SIZEMIN+1> Y_w_frac = (coeff1 * din[0] + coeff2 * din[1] + coeff3 * din[2]);
  ap_int<SIZE+1+SIZEMIN+1> U_w_frac = (coeff4 * din[0] + coeff5 * din[1] + din[2] * coeff8 + (128 << SIZE));
  ap_int<SIZE+1+SIZEMIN+1> V_w_frac = (din[0] * coeff8 + coeff6 * din[1] + coeff7 * din[2] + (128 << SIZE));

  ap_int<SIZEMIN+2> Y_wo_frac = (Y_w_frac >> SIZE);
  ap_int<SIZEMIN+2> U_wo_frac = (U_w_frac >> SIZE);
  ap_int<SIZEMIN+2> V_wo_frac = (V_w_frac >> SIZE);

  ap_uint<SIZEMIN> Y = 0;
  ap_uint<SIZEMIN> U = 0;
  ap_uint<SIZEMIN> V = 0;

  if( Y_wo_frac > 255 )
    Y = 255;
  else if( Y_wo_frac < 0 )
    Y =   0;
  else
    Y = Y_wo_frac;

  if( U_wo_frac > 255 )
    U = 255;
  else if( U_wo_frac < 0 )
    U =   0;
  else
    U = U_wo_frac;

  if( V_wo_frac > 255 )
      V = 255;
    else if( V_wo_frac < 0 )
      V =   0;
    else
      V = V_wo_frac;


  dout[0] = (uint8_t) Y;
  dout[1] = (uint8_t) U;
  dout[2] = (uint8_t) V;
}
