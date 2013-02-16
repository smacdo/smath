/*
 * Copyright 2010-2013 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <smath/util.h>
#include <smath/config.h>

/**
 * Calculate the square root of a value using a fast approximation method.
 *
 * Credit for the original implementation of fastSqrt goes to the Quake III
 * arena source code. More information about this can be read on Wikipedia:
 *   http://en.wikipedia.org/wiki/Fast_inverse_square_root
 */
float Math::fastSqrt( float v )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = v * 0.5f;
    y  = v;
    i  = *( long *) &y;             // evil floating point bit level hack
    i  = 0x5f3759df - ( i >> 1 );   // seriously, wtf
    y  = *( float *) &i;            // more magic
    y  = y * (threehalfs - (x2 * y * y));   // 1st iteration
//  y  = y * (threehalfs - (x2 * y * y));   // 2nd itr, can be removed

    return y;
}
