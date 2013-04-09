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

#include <smath/vector.h>
#include <smath/config.h>

/**
 * 2d axis aligned rectangle.
 */
class RectF
{
public:
    RectF( const TVector2<float>& topLeft, const TVector2<float>& rectSize )
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

    TVector2<float> position() const
    {
        return mTopLeft;
    }

    TVector2<float> topLeft() const
    {
        return mTopLeft;
    }

    TVector2<float> topRight() const
    {
        return TVector2<float>( mTopLeft.x() + mSize.x(), mTopLeft.y() );
    }

    TVector2<float> bottomLeft() const
    {
        return TVector2<float>( mTopLeft.x(), mTopLeft.y() + mSize.y() );
    }
    
    TVector2<float> bottomRight() const
    {
        return mTopLeft + mSize;
    }

    TVector2<float> center() const
    {
        return ( mTopLeft + mSize ) / 2.0f;
    }

    TVector2<float> size() const
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

    void move( const TVector2<float>& delta )
    {
        mTopLeft += delta;
    }

    void moveTo( const TVector2<float>& position )
    {
        mTopLeft = position;
    }

    void adjustSize( const TVector2<float>& newSize )
    {
        mSize += newSize;
        SMATH_ASSERT( mSize.x() > 0.0f && mSize.y() > 0.0f, "Invalid dimensions" );
    }

    void resize( const TVector2<float>& newSize )
    {
        SMATH_ASSERT( newSize.x() > 0.0f && newSize.y() > 0.0f, "Invalid dimensions" );
        mSize = newSize;
    }

    void resize( float width, float height )
    {
        resize( TVector2<float>( width, height ) );
    }

    bool contains( const TVector2<float>& point ) const
    {
        TVector2<float> pt = point - mTopLeft;

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

    float area() const
    {
        return mSize.x() * mSize.y();
    }

private:
    TVector2<float> mTopLeft;
    TVector2<float> mSize;
};

#endif

