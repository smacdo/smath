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
#include <smath/randomstate.h>
#include <algorithm>
#include <cassert>

using namespace RandomConstants;

random_state_t::random_state_t()
    : vals(),
      seed( 0u ),
      index( 0u )
{
}

random_state_t::random_state_t( const random_state_t& rhs )
    : vals(),
      seed( rhs.seed ),
      index( rhs.index )
{
    std::copy( &rhs.vals[0], &rhs.vals[N], &vals[0] );
}

random_state_t::random_state_t( const random_state_t* rhs )
    : vals(),
      seed(),
      index()
{
    assert( rhs != NULL );

    seed = rhs->seed;
    index = rhs->index;

    std::copy( &rhs->vals[0], &rhs->vals[N], &vals[0] );
}


random_state_t::~random_state_t()
{
    // empty
}

random_state_t& random_state_t::operator = ( const random_state_t& rhs )
{
    if ( &rhs != this )
    {
        seed  = rhs.seed;
        index = rhs.index;

        std::copy( &rhs.vals[0], &rhs.vals[N], &vals[0] );
    }

    return *this;
}
