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
#include <smath/vector.h>
#include <smath/util.h>
#include <cmath>

template<>
scalar_t length( const TVector4<scalar_t>& v )
{
    return sqrt( lengthSquared( v ) );
}

template<>
scalar_t length( const TVector3<scalar_t>& v )
{
    return sqrt( lengthSquared( v ) );
}

template<>
scalar_t length( const TVector2<scalar_t>& v )
{
    return sqrt( lengthSquared( v ) );
}

template<>
scalar_t angleBetween( const TVector3<scalar_t>& lhs,
                       const TVector3<scalar_t>& rhs )
{
    scalar_t a = acos( dot( lhs, rhs ) / ( length( lhs ) * length( rhs ) ) );
    return a * static_cast<scalar_t>(180) / Math::Pi;
}

template<>
TVector4<scalar_t> normalized( const TVector4<scalar_t>& v )
{
    scalar_t len = length( v );
    SMATH_ASSERT( len > 0.0f, "Cannot normalize vector of length zero" );

    // If the vector is already normalized (length is one), then simply return
    // the vector without re normalizing it
    if ( Math::equalsClose( len, static_cast<scalar_t>(1) ) )
    {
        return TVector4<scalar_t>( v.mX, v.mY, v.mZ, v.mW );
    }
    else
    {
        return TVector4<scalar_t>( v.mX / len, v.mY / len, v.mZ / len, v.mW / len );
    }
}

template<>
TVector3<scalar_t> normalized( const TVector3<scalar_t>& v )
{
    scalar_t len = length( v );
    SMATH_ASSERT( len > 0.0f, "Cannot normalize vector of length zero" );

    // If the vector is already normalized (length is one), then simply return
    // the vector without re normalizing it
    if ( Math::equalsClose( len, static_cast<scalar_t>(1) ) )
    {
        return TVector3<scalar_t>( v.mX, v.mY, v.mZ );
    }
    else
    {
        return TVector3<scalar_t>( v.mX / len, v.mY / len, v.mZ / len );
    }
}

template<>
TVector2<scalar_t> normalized( const TVector2<scalar_t>& v )
{
    scalar_t len = length( v );
    SMATH_ASSERT( len > 0.0f, "Cannot normalize vector of length zero" );

    // If the vector is already normalized (length is one), then simply return
    // the vector without re normalizing it
    if ( Math::equalsClose( len, static_cast<scalar_t>(1) ) )
    {
        return TVector2<scalar_t>( v.mX, v.mY );
    }
    else
    {
        return TVector2<scalar_t>( v.mX / len, v.mY / len );
    }
}

template<>
TVector3<scalar_t> rotateAroundX( const TVector3<scalar_t>& v, scalar_t angle )
{
    if ( Math::notZero( angle ) )
    {
        scalar_t sangle = sin( Math::Pi * angle / 180.0f );
        scalar_t cangle = cos( Math::Pi * angle / 180.0f );

        return TVector3<scalar_t>( v.mX,
                                   v.mY * cangle - v.mZ * sangle,
                                   v.mY * sangle + v.mZ * cangle );
    }
    else
    {
        return v;
    }
}

template<>
TVector3<scalar_t> rotateAroundY( const TVector3<scalar_t>& v, scalar_t angle )
{
    if ( Math::notZero( angle ) )
    {
        scalar_t sangle = sin( Math::Pi * angle / 180.0f );
        scalar_t cangle = cos( Math::Pi * angle / 180.0f );

        return TVector3<scalar_t>( v.mX * cangle + v.mZ * sangle,
                                   v.mY,
                                  -v.mX * sangle + v.mZ * cangle );
    }
    else
    {
        return v;
    }
}

template<>
TVector3<scalar_t> rotateAroundZ( const TVector3<scalar_t>& v, scalar_t angle )
{
    if ( Math::notZero( angle ) )
    {
        scalar_t sangle = sinf( Math::Pi * angle / 180.0f );
        scalar_t cangle = cosf( Math::Pi * angle / 180.0f );

        return TVector3<scalar_t>( v.mX * cangle - v.mY * sangle,
                                   v.mY * sangle + v.mY * cangle,
                                   v.mZ );
    }
    else
    {
        return v;
    }
}

template<>
TVector3<scalar_t> rotateAround( const TVector3<scalar_t>& v,
                                 const TVector3<scalar_t>& axis,
                                 scalar_t angle )
{
	scalar_t one = static_cast<scalar_t>(1);

    if ( Math::notZero( angle ) )
    {
        scalar_t sangle = sin( Math::Pi * angle / 180.0f );
        scalar_t cangle = cos( Math::Pi * angle / 180.0f );
        scalar_t xangle = one - cangle;    // "1 minus cos angle"

        TVector3<scalar_t> u  = normalized( axis );
        TVector3<scalar_t> r1( u.mX * u.mX + cangle * ( one - u.mX * u.mX ),
                               u.mX * u.mY * xangle - sangle * u.mZ,
                               u.mY * u.mZ * xangle + sangle * u.mY );
        TVector3<scalar_t> r2( u.mX * u.mY * xangle + sangle * u.mZ,
                               u.mY * u.mY + cangle * ( one - u.mY * u.mY ),
                               u.mY * u.mZ * xangle - sangle * u.mX );
        TVector3<scalar_t> r3( u.mX * u.mZ * xangle - sangle * u.mY,
                               u.mY * u.mZ * xangle + sangle * u.mX,
                               u.mZ * u.mZ + cangle * ( one - u.mZ * u.mZ ) );

        return TVector3<scalar_t>( dot( v, r1 ),
                                   dot( v, r2 ),
                                   dot( v, r3 ) );
    }
    else
    {
        return v;
    }
}

