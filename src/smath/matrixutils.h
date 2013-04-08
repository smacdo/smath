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
#ifndef SCOTT_MATH_MATRIX_UTILS_H
#define SCOTT_MATH_MATRIX_UTILS_H

#include <smath/matrix.h>
#include <smath/vector.h>

namespace Math
{
    /**
     * Generates a new matrix that rotates around the X axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundX( T angle )
    {
        T s = sinf( angle );
        T c = cosf( angle );

        return TMatrix4<T>( 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, c,    -s,   0.0f,
                            0.0f, s,     c,   0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Generates a new matrix that rotates around the Y axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundY( T angle )
    {
        T s = sinf( angle );
        T c = cosf( angle );

        return TMatrix4<T>( c,    0.0f, s,    0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            -s,   0.0f, c,    0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Generates a new matrix that rotates around the Z axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundZ( T angle )
    {
        T s = sinf( angle );
        T c = cosf( angle );

        return TMatrix4<T>( c,    -s,   0.0f, 0.0f,
                            s,    c,    0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Generates a new matrix that rotates any given vector around the
     * specified axis.
     *  Source: Sean Barrett's stb_vec.h
     */
    template<typename T>
    TMatrix4<T> createRotationAroundAxis( const TVector3<T>& axis, T angle )
    {
        T s  = sin( angle );
        T c  = cos( angle );
        T ic = 1 - c;

        TVector3<T> p = normalized( axis );

        T x = p.x();
        T y = p.y();
        T z = p.z();

        T m00 = c + ic * x * x;
        T m01 = ic * x * y + s * z;
        T m02 = ic * x * z - s * y;

        T m10 = ic * y * x - s * z;
        T m11 = c + ic * y * y ;
        T m12 = ic * y * z + s * x;

        T m20 = ic * z * x + s * y;
        T m21 = ic * z * y - s * x;
        T m22 = c + ic * z * z;

        return TMatrix4<T>( m00,  m01, m02, 0,
                            m10,  m11, m12, 0,
                            m20,  m21, m22, 0,
                            0,    0,   0,   1 );
    }

    /**
     * Creates a translation matrix
     */
    template<typename T>
    TMatrix4<T> createTranslation( T x, T y, T z )
    {
        return TMatrix4<T>( 1.0f, 0.0f, 0.0f, x,
                            0.0f, 1.0f, 0.0f, y,
                            0.0f, 0.0f, 1.0f, z,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Creates a uniform scaling matrix
     */
    template<typename T>
    TMatrix4<T> createScale( T k )
    {
        return TMatrix4<T>( k,    0.0f, 0.0f, 0.0f,
                            0.0f, k,    0.0f, 0.0f,
                            0.0f, 0.0f, k,    0.0f,
                            1.0f, 1.0f, 1.0f, 1.0f );
    }

    /**
     * Creates a view matrix that looks from a specified eye position to
     * the center position and with the given up vector.
     *
     * Similiar to gluLookAt
     */
    template<typename T>
    TMatrix4<T> createLookAt( const TVector3<T>& /*eye*/,
                              const TVector3<T>& /*lookAt*/,
                              const TVector3<T>& /*up*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates an OpenGL compatible perspective projection
     */
    template<typename T>
    TMatrix4<T> createFrustum( T /*left*/,
                               T /*right*/,
                               T /*bottom*/,
                               T /*top*/,
                               T /*zNear*/,
                               T /*zFar*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates an OpenGL compatible orthographic projection matrix
     */
    template<typename T>
    TMatrix4<T> createOrtho( T /*left*/,
                             T /*right*/,
                             T /*bottom*/,
                             T /*top*/,
                             T /*zNear*/,
                             T /*zFar*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates a matrix using parameters specified in row order form
     */
    template<typename T>
    TMatrix4<T> createRowOrder()
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates a matrix using parameters specified in column order form
     */
    template<typename T>
    TMatrix4<T> createColOrder()
    {
        return TMatrix4<T>::IDENTITY;
    }
};

#endif
