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
#ifndef SCOTT_MATH_RECT_H
#define SCOTT_MATH_RECT_H

// TODO: Convert floats to scalar_t

#include <smath/vector.h>
#include <smath/config.h>

/**
 * 2d axis aligned rectangle.
 */
class RectF
{
public:
    RectF( const TVector2<scalar_t>& topLeft, const TVector2<scalar_t>& rectSize )
        : mTopLeft( topLeft ),
          mSize( rectSize )
    {
        SMATH_ASSERT( mSize.x() > 0.0f && mSize.y() > 0.0f, "Invalid dimensions" );
    }

    RectF( float topX, float topY, float width, float height )
        : mTopLeft( topX, topY ),
          mSize( width, height )
    {
        SMATH_ASSERT( width > 0.0f && height > 0.0f, "Invalid dimensions" );
    }

    RectF( const RectF& rect )
        : mTopLeft( rect.mTopLeft ),
          mSize( rect.mSize )
    {
    }

    RectF& operator = ( const RectF& rect )
    {
        mTopLeft = rect.mTopLeft;
        mSize    = rect.mSize;

        return *this;
    }

    bool operator == ( const RectF& rect ) const
    {
        return ( mTopLeft == rect.mTopLeft && mSize == rect.mSize );
    }

    bool operator != ( const RectF& rect ) const
    {
        return !( mTopLeft == rect.mTopLeft && mSize == rect.mSize ); 
    }

    TVector2<scalar_t> position() const
    {
        return mTopLeft;
    }

    TVector2<scalar_t> topLeft() const
    {
        return mTopLeft;
    }

    TVector2<scalar_t> topRight() const
    {
        return TVector2<scalar_t>( mTopLeft.x() + mSize.x(), mTopLeft.y() );
    }

    TVector2<scalar_t> bottomLeft() const
    {
        return TVector2<scalar_t>( mTopLeft.x(), mTopLeft.y() + mSize.y() );
    }
    
    TVector2<scalar_t> bottomRight() const
    {
        return mTopLeft + mSize;
    }

    TVector2<scalar_t> center() const
    {
        return ( mTopLeft + mSize ) / 2.0f;
    }

    TVector2<scalar_t> size() const
    {
        return mSize;
    }

    float top() const
    {
        return mTopLeft.y();
    }

    float left() const
    {
        return mTopLeft.x();
    }

    float right() const
    {
        return mTopLeft.x() + mSize.x();
    }

    float bottom() const
    {
        return mTopLeft.y() + mSize.y();
    }

    float width() const
    {
        return mSize.x();
    }

    float height() const
    {
        return mSize.y();
    }

    void move( const TVector2<scalar_t>& delta )
    {
        mTopLeft += delta;
    }

    void moveTo( const TVector2<scalar_t>& position )
    {
        mTopLeft = position;
    }

    void adjustSize( const TVector2<scalar_t>& newSize )
    {
        mSize += newSize;
        SMATH_ASSERT( mSize.x() > 0.0f && mSize.y() > 0.0f, "Invalid dimensions" );
    }

    void resize( const TVector2<scalar_t>& newSize )
    {
        SMATH_ASSERT( newSize.x() > 0.0f && newSize.y() > 0.0f, "Invalid dimensions" );
        mSize = newSize;
    }

    void resize( float width, float height )
    {
        resize( TVector2<scalar_t>( width, height ) );
    }

    bool contains( const TVector2<scalar_t>& point ) const
    {
        TVector2<scalar_t> pt = point - mTopLeft;

        return ( pt.x() >= 0.0f && pt.x() <= mSize.x() &&
                 pt.y() >= 0.0f && pt.y() <= mSize.y() );
    }

    bool contains( const RectF& /*rect*/ ) const
    {
        return false;
    }

    bool intersects( const RectF& /*rect*/ ) const
    {
        return false;
    }

private:
    TVector2<scalar_t> mTopLeft;
    TVector2<scalar_t> mSize;
};

#endif

