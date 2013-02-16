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
 * Computes a 32 bit hash from a floating point value. This is used to
 * quickly cache floats into a hashmap, but care must be taken since two
 * seemingly identical floating point values can have different memory values
 * and hence different hash values
 */
inline unsigned int hashfloat( float value )
{
    const unsigned int *intPtr =
        reinterpret_cast<unsigned int *>( &value );
    return *intPtr;
}

/**
 * Computes an unsigned 32 bit hash value from an array of floating
 * point values.
 */
inline unsigned int hashfloat( const float * pArray, size_t arraySize )
{
    unsigned int hash             = 0u;
    const unsigned int *pIntArray =
        reinterpret_cast<const unsigned int*>( pArray );

    for ( size_t i = 0; i < arraySize; ++i )
    {
        hash ^= pIntArray[i];
    }

    return hash;
}
