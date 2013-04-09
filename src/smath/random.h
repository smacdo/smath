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
#ifndef SCOTT_MATH_RANDOM_H
#define SCOTT_MATH_RANDOM_H

#include <stdint.h>
#include <cstdlib>
#include <algorithm>

namespace MT19937Constants
{
    const uint32_t N = 624;
    const uint32_t M = 396;
    const uint32_t MATRIX_A = 0x9908B0DFU;
    const uint32_t UPPER_MASK = 0x80000000U;
    const uint32_t LOWER_MASK = 0x7fffffffU;
    const uint32_t INITIAL_SEED = 5489U;
}

/**
 * Random number generator.
 * [NEEDS MORE DESCRIPTION]
 */
class Random
{
public:
    Random();
    Random( uint32_t seed );
    Random( const Random& r );
    ~Random();

    Random& operator = ( const Random& rhs );
    
    int nextInt();
    int nextInt( int max );
    int nextInt( int min, int max );

    unsigned int nextUInt();
    unsigned int nextUInt( unsigned int max );
    unsigned int nextUInt( unsigned int min, unsigned int max );

    float nextFloat();
    float nextFloat( float min, float max );

    float nextFloat2();
    float nextFloat3();

    double nextDouble();

    bool nextBool();
    void nextBytes( std::vector<uint8_t>& array, size_t count );

    float nextGaussian();
    float nextGaussian( float standardDeviation, float mean );
    float nextGaussian( float standardDeviation, float mean, float min, float max );

private:
    void init( uint32_t seed );
    void initByArray( uint32_t key[], size_t length );

private:
    uint32_t mState[MT19937Constants::N];
    uint32_t mSeed;
    size_t mIndex;
    bool mHasNextGaussian;
    float mNextGaussian;
};

#endif

