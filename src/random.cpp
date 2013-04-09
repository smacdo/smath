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

//
//  C++ implementation of the MT19937 random number generator. The original implementation was
//  coded by Takuji Nishmura and Makoto Matsumoto. Modified and ported to C++ by Scott MacDonald
//  on 2013/03/25. The generators returning floating point values are based on code written by
//  Isaku Wada, 2002/01/09. The original license is reproduced below:
//
// A C-program for MT19937, with initialization improved 2002/1/26.
// Coded by Takuji Nishimura and Makoto Matsumoto.
//
// Before using, initialize the state by using init_genrand(seed)  
// or init_by_array(init_key, key_length).
//
// Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
// are met:
//
//   1. Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//   3. The names of its contributors may not be used to endorse or promote 
//      products derived from this software without specific prior written 
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Any feedback is very welcome.
// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
// email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
//
// ---
//
// Feedback about this C++ port should be sent to Scott MacDonald. See
// http://whitespaceconsideredharmful.com/ for contact information.
#include <smath/random.h>
#include <smath/util.h>

#include <cassert>
#include <stdint.h>

using namespace MT19937Constants;

Random::Random()
    : mSeed( INITIAL_SEED ),
      mIndex( 0u ),
      mHasNextGaussian( false ),
      mNextGaussian( 0 )
{
    init( mSeed );
}

Random::Random( uint32_t seed )
    : mSeed( seed ),
      mIndex( 0u ),
      mHasNextGaussian( false ),
      mNextGaussian( 0 )
{
    init( mSeed );
}

Random::Random( const Random& v )
    : mSeed( v.mSeed ),
      mIndex( v.mIndex ),
      mHasNextGaussian( v.mHasNextGaussian ),
      mNextGaussian( v.mNextGaussian )
{
    std::copy( &v.mState[0], &v.mState[N], &mState[0] );
}

Random::~Random()
{
    // empty
}

Random& Random::operator = ( const Random& rhs )
{
    if ( this != &rhs )
    {
        mSeed  = rhs.mSeed;
        mIndex = rhs.mIndex;
    
        std::copy( &rhs.mState[0], &rhs.mState[N], &mState[0] );
    }

    return *this;
}

void Random::init( uint32_t seed )
{
    mState[0] = seed & 0xffffffffUL;

    for ( mIndex = 1; mIndex < N; ++mIndex )
    {
        mState[mIndex] = (1812433253UL * (mState[mIndex-1] ^ (mState[mIndex-1] >> 30)) + mIndex);

        // See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
        // In the previous versions, MSBs of the seed affect
        // only MSBs of the array mt[].
        // 2002/01/09 modified by Makoto Matsumoto
        mState[mIndex] &= 0xffffffffUL; // for 32 bit machines
    }
}

void Random::initByArray( uint32_t key[], size_t length )
{
    size_t i = 1, j = 0;
    int k = ( N > length ? N : length );
    init( 19650218UL );     // what's this magic number represent?

    for ( ; k; --k )
    {
        mState[i]  = ( mState[i] ^ (( mState[i - 1] ^ ( mState[i-1] >> 30 )) * 1664525UL))
            + key[j] + j;   // non-linear... ?
        mState[i] &= 0xffffffffUL; // for WORDSIZE > 32 machines

        i++;
        j++;

        if ( i >= N )
        {
            mState[0] = mState[N - 1];
            i = 1;
        }

        if ( j >= length )
        {
            j = 0;
        }
    }

    for ( k = N - 1; k; k-- )
    {
        mState[i]  = ( mState[i] ^ (( mState[i - 1] ^ ( mState[i - 1] >> 30 )) ^ 1566083941UL))
            - i; // non linear. again - ?
        mState[i] &= 0xffffffffUL; // for WORDSIZE > 32 machines

        i++;

        if ( i >= N )
        {
            mState[0] = mState[N - 1];
            i = 1;
        }
    }
    
    mState[0] = 0x80000000UL; // MSB is 1; assuring non-zero initial array
}

unsigned int Random::nextUInt()
{
    static uint32_t MAG01[2] = { 0x0UL, MATRIX_A };
    uint32_t y;

    if ( mIndex >= N )          // Generate N words at a time
    {
        uint32_t kk;

        if ( mIndex == N+1 )        // if init() has not been called (remove this)
        {
            init( INITIAL_SEED );
        }

        for ( kk = 0; kk < N - M; ++kk )
        {
            y = ( mState[kk] & UPPER_MASK ) | ( mState[kk+1] & LOWER_MASK );
            mState[kk] = mState[kk + M] ^ ( y >> 1 ) ^ MAG01[y & 0x1UL];
        }

        for ( ; kk < N - 1; ++kk )
        {
            y = ( mState[kk] & UPPER_MASK ) | ( mState[kk + 1] & LOWER_MASK );
            mState[kk] = mState[kk + ( M - N )] ^ ( y >> 1 ) ^ MAG01[y & 0x1UL];
        }

        y = ( mState[N - 1] & UPPER_MASK ) | ( mState[0] & LOWER_MASK );
        mState[N-1] = mState[M - 1] ^ ( y >> 1 ) ^ MAG01[y & 0x1UL];

        mIndex = 0;
    }

    // Get next random value in sequence
    y = mState[ mIndex++ ];

    // Tempering
    y ^= ( y >> 11 );
    y ^= ( y << 7 )  & 0x9d2c5680U;
    y ^= ( y << 15 ) & 0xefc60000U;
    y ^= ( y >> 18 );

    return y;
}

// Generates a random number on the [0,2**32-1] interval.
//   Basically gives you a random number from [0,MAX_INT].
int Random::nextInt()
{
    return static_cast<int>( nextUInt() >> 1 );
}

int Random::nextInt( int max )
{
    return nextInt( 0, max );
}


/**
 * Returns a random value between [min, max]. The minimum value must be zero or greater.
 *
 * TODO: This generation is numerically biased, and I think there are better ways of
 *       doing this for small ranges. Not sure?
 */
int Random::nextInt( int min, int max )
{
    return min + nextInt() % ( max - min + 1 );
}

// [0,1]
float Random::nextFloat()
{
    float value = static_cast<float>( nextUInt()) ;
    return value * ( 1.0f / 4294967295.0f );    // divide by 2^32-1
}

// [0,1)
float Random::nextFloat2() // need better name
{
    float value = static_cast<float>( nextUInt()) ;
    return value * ( 1.0f / 4294967296.0f );    // divide by 2^32
}

// (0,1)
float Random::nextFloat3() // need better name
{
    float value = static_cast<float>( nextUInt());
    return ( value + 0.5f ) * ( 1.0f / 4294967296.0f );
}

// Generate random number with 53 bit resolution (almost double)
double Random::nextDouble()
{
    float a = static_cast<float>( nextUInt() >> 5 );
    float b = static_cast<float>( nextUInt() >> 6 );

    return ( a * 67108864.0 + b )* ( 1.0 / 9007199254740992.0 );
}

bool Random::nextBool()
{
    return 1 == ( rand() % 2 );
}

void Random::nextBytes( std::vector<uint8_t>& bytes, size_t count )
{
    assert( count < bytes.size() );
    size_t i = 0;

    // Fill the provided byte array with random values, filling it in increments of four.
    for ( i = 0; i < count; i += 4 )
    {
        unsigned int v = nextUInt();

        bytes[i + 0] = static_cast<uint8_t>( v & 0xFF );
        bytes[i + 1] = static_cast<uint8_t>( ( v >> 8  ) & 0xFF );
        bytes[i + 2] = static_cast<uint8_t>( ( v >> 16 ) & 0xFF );
        bytes[i + 3] = static_cast<uint8_t>( ( v >> 24 ) & 0xFF );
    }

    // Fill the remaining buckets before finishing.
    unsigned int v = nextUInt();

    switch ( count - i )
    {
        case 3:
            bytes[i + 0] = static_cast<uint8_t>( v & 0xFF );

        case 2:
            bytes[i + 1] = static_cast<uint8_t>( ( v >> 8 ) & 0xFF );

        case 1:
            bytes[i + 2] = static_cast<uint8_t>( ( v >> 16 ) & 0xFF );
            break;
    }
}

float Random::nextGaussian()
{
    float v1 = 0.0f, v2 = 0.0f, s = 0.0f;

    if ( mHasNextGaussian )
    {
        mHasNextGaussian = false;
        return mNextGaussian;
    }

    do
    {
        v1 = 2.0f * nextFloat() - 1.0f;
        v2 = 2.0f * nextFloat() - 1.0f;
        s = v1 * v1 + v2 * v2;
    }
    while ( s == 0.0f || s >= 1.0f );

    float multiplier = sqrt( -2 * log( s ) / s );

    mNextGaussian    = v2 * multiplier;
    mHasNextGaussian = true;

    return v1 * multiplier;
}

float Random::nextGaussian( float standardDeviation, float mean )
{
    return nextGaussian() * standardDeviation + mean;
}

float Random::nextGaussian( float standardDeviation, float mean, float min, float max )
{
    float v = nextGaussian() * standardDeviation + mean;
    return Math::clamp( v, min, max );
}
