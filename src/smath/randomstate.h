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
#ifndef SCOTT_RANDOM_STATE_H
#define SCOTT_RANDOM_STATE_H

//#define MATH_USE_STD_RANDOM

#ifdef MATH_USE_STD_RANDOM
#include <random>

struct random_state_t
{
    std::mt19937 rng;
};

#else
#include <cstddef>
#include <stdint.h>

namespace RandomConstants
{
    const uint32_t N = 624;
    const uint32_t M = 396;
    const uint32_t MATRIX_A = 0x9908B0DFU;
    const uint32_t UPPER_MASK = 0x80000000U;
    const uint32_t LOWER_MASK = 0x7fffffffU;
    const uint32_t INITIAL_SEED = 5489U;
}

struct random_state_t
{
    random_state_t();
    random_state_t( const random_state_t& rhs );
    random_state_t( const random_state_t *rhs );

    ~random_state_t();

    random_state_t& operator = ( const random_state_t& rhs );

    uint32_t vals[RandomConstants::N];
    uint32_t seed;
    size_t index;
};
#endif

#endif
