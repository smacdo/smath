/**
 * Unit tests for templated vector2 class. These tests use float32 for the
 * numeric type, but can be adjusted to double precision.
 */
#include <gtest/gtest.h>
#include <smath/vector.h>

#include "unittesthelpers.h"

#ifndef MATH_TYPEDEFS
typedef TVector2<float> Vec2;
#endif

TEST(Math, Vector2_DefaultContructor)
{
    const Vec2 v;
    EXPECT_TRUE( true );      // test here just to make sure it compiles
}

TEST(Math, Vector2_SizeTest)
{
    const Vec2 v( 1.0f, 2.0f );
    EXPECT_EQ( sizeof(float) * 2, sizeof(v) );
}

TEST(Math, Vector2_MemoryArrayTest)
{
    // Makes sure that a vector is laid out linearly in memory
    Vec2 v[3];

    v[0] = Vec2( 1.0f, 2.0f );
    v[1] = Vec2( 3.0f, 4.0f );
    v[2] = Vec2( 5.0f, 6.0f );

    const float * pVals = v[0].const_ptr();

    EXPECT_FLOAT_EQ( 1.0f, *(pVals + 0) );
    EXPECT_FLOAT_EQ( 2.0f, *(pVals + 1) );
    EXPECT_FLOAT_EQ( 3.0f, *(pVals + 2) );
    EXPECT_FLOAT_EQ( 4.0f, *(pVals + 3) );
    EXPECT_FLOAT_EQ( 5.0f, *(pVals + 4) );
    EXPECT_FLOAT_EQ( 6.0f, *(pVals + 5) );
}

TEST(Math, Vector2_PointerConstructor)
{
    float values[5] = { 3.0f, 2.0f, 5.0f, -3.0f, 6.0f };
    Vec2 v( &values[1] );

    EXPECT_FLOAT_EQ(  2.0f, v[0] );
    EXPECT_FLOAT_EQ(  5.0f, v[1] );
}

TEST(Math, Vector2_ValueConstructor)
{
    const Vec2 v( 1.0f, -2.0f );

    EXPECT_FLOAT_EQ(  1.0f, v[0] );
    EXPECT_FLOAT_EQ( -2.0f, v[1] );
}

TEST(Math, Vector2_CopyConstructor)
{
    const Vec2 a( 1.0f, -2.0f );
    const Vec2 b( a );

    EXPECT_FLOAT_EQ(  1.0f, b[0] );
    EXPECT_FLOAT_EQ( -2.0f, b[1] );
}

TEST(Math, Vector2_ConstIndexOperatorRead)
{
    const Vec2 v( 1.0f, -2.0f );

    EXPECT_FLOAT_EQ(  1.0f, v[0] );
    EXPECT_FLOAT_EQ( -2.0f, v[1] );
}

TEST(Math, Vector2_IndexOperatorWrite)
{
    Vec2 v( 1.0f, -2.0f );

    v[0] = 2.0f;
    v[1] = 0.2f;

    EXPECT_EQ( Vec2( 2.0f, 0.2f ), v );
}

TEST(Math, Vector2_ConstPointerAccess)
{
    Vec2 v( 1.0f, 2.0f );
    const float * ptr = v.ptr();

    EXPECT_FLOAT_EQ( 1.0f, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0f, ptr[1] );
}

TEST(Math, Vector2_ConstConstPointerAccess)
{
    Vec2 v( 1.0f, 2.0f );
    const float * ptr = v.const_ptr();

    EXPECT_FLOAT_EQ( 1.0f, ptr[0] );
    EXPECT_FLOAT_EQ( 2.0f, ptr[1] );
}

TEST(Math, Vector2_NonConstPointerReadAndWrite)
{
    Vec2 v( 1.0f, 2.0f );
    float * ptr = v.ptr();

    EXPECT_EQ( Vec2( 1.0f, 2.0f ), v );

    ptr[0] = 5.0f;
    ptr[1] = 6.0f;

    EXPECT_EQ( Vec2( 5.0f, 6.0f ), v );
}

TEST(Math, Vector2_Assignment)
{
    Vec2 a( 1.0f, 2.0f );
    const Vec2 b( 3.0f, 4.0f );
    
    a = b;

    EXPECT_NE( Vec2( 1.0f, 2.0f ), a );
    EXPECT_EQ( Vec2( 3.0f, 4.0f ), a );
}

TEST(Math, Vector2_EqualityOperator)
{
    const Vec2 a( 1.5f, -0.2f );
    const Vec2 b( 1.5f,  0.2f );
    const Vec2 c( 0.5f, -0.2f );
    const Vec2 e( 0.0f,  0.5f );
    const Vec2 f( 1.5f, -0.2f );

    EXPECT_EQ( a, f );
    EXPECT_EQ( a, a );
    EXPECT_FALSE( a == b );
    EXPECT_FALSE( a == c );
    EXPECT_FALSE( a == e );
    EXPECT_TRUE( a == f );
    EXPECT_TRUE( a == a );
}

TEST(Math, Vector2_EqualityOperatorPrecision)
{
    const Vec2 a( 2.2f, -0.333f );
    const Vec2 b( 4.4f/2.0f, -0.999f/3.0f );

    EXPECT_EQ( a, b );
}

TEST(Math, Vector2_InequalityOperator)
{
    const Vec2 a( 1.5f, -0.2f );
    const Vec2 b( 1.5f,  0.2f );
    const Vec2 c( 0.5f, -0.2f );
    const Vec2 e( 0.0f,  0.5f );
    const Vec2 f( 1.5f, -0.2f );

    EXPECT_TRUE( a != b );
    EXPECT_TRUE( a != c );
    EXPECT_TRUE( a != e );
    EXPECT_FALSE( a != f );
    EXPECT_FALSE( a != a );
}


TEST(Math, Vector2_Negation)
{
    Vec2 a( 2.0f, 0.0f );
    a = -a;

    EXPECT_EQ( Vec2( -2.0f, -0.0f ), a );
    EXPECT_EQ( Vec2( -2.0f,  0.0f ), a );    // close
}

TEST(Math, Vector2_AdditionOperator)
{
    const Vec2 a( 3.0f, 5.0f );
    const Vec2 b(-4.0f, 6.0f );

    EXPECT_EQ( Vec2( -1.0f, 11.0f ), a + b );
}

TEST(Math, Vector2_SelfAdditionOperator)
{
          Vec2 a( 3.0f, 5.0f );
    const Vec2 b(-4.0f, 6.0f );

    a += b;

    EXPECT_EQ( Vec2( -1.0f, 11.0f ), a );
}

TEST(Math, Vector2_SubtractionOperator)
{
    const Vec2 a( 5.0f, 2.0f );
    const Vec2 b(-1.0f, 3.0f );
    const Vec2 c = a - b;
    
    EXPECT_FLOAT_EQ(   6.0f, c[0] );
    EXPECT_FLOAT_EQ(  -1.0f, c[1] );
}

TEST(Math, Vector2_SelfSubtractionOperator)
{
    Vec2       a( 5.0f, 2.0f );
    const Vec2 b(-1.0f, 3.0f );
    a -= b;
    
    EXPECT_FLOAT_EQ(   6.0f, a[0] );
    EXPECT_FLOAT_EQ(  -1.0f, a[1] );
}

TEST(Math, Vector2_MultiplyOperator)
{
    const Vec2 a( 3.0f, 5.0f );
    const Vec2 b = a * 2.0f;

    EXPECT_EQ( Vec2( 6.0f, 10.0f ), b );
}

TEST(Math, Vector2_SelfMultiplyOperator)
{
    Vec2 a( 3.0f, 5.0f );
    a *= 2.0f;

    EXPECT_EQ( Vec2( 6.0f, 10.0f ), a );
}

TEST(Math, Vector2_DivisionOperator)
{
    const Vec2 a( 3.0f, 5.0f );
    const Vec2 b = a / 2.0f;

    EXPECT_EQ( Vec2( 1.5f, 2.5f ), b );
}

TEST(Math, Vector2_SelfDivisionOperator)
{
    Vec2 a( 3.0f, 5.0f );
    a /= 2.0f;

    EXPECT_EQ( Vec2( 1.5f, 2.5f ), a );
}

TEST(Math, Vector2_XAccessor)
{
    Vec2 a( 1.0f, 2.0f );
    Vec2 b( 6.0f, 5.0f );

    EXPECT_FLOAT_EQ( 1.0f, a.x() );
    EXPECT_FLOAT_EQ( 6.0f, b.x() );
}

TEST(Math, Vector2_YAccessor)
{
    Vec2 a( 1.0f, 2.0f );
    Vec2 b( 6.0f, 5.0f );

    EXPECT_FLOAT_EQ( 2.0f, a.y() );
    EXPECT_FLOAT_EQ( 5.0f, b.y() );
}

TEST(Math, Vector2_ZeroVector)
{
    const Vec2 a = Vec2::ZERO;

    EXPECT_FLOAT_EQ( a[0], 0.0f );
    EXPECT_FLOAT_EQ( a[1], 0.0f );
}

TEST(Math, Vector2_ZeroVectorIsZeroValueConstructed)
{
    const Vec2 a( 0.0f, 0.0f );
    const Vec2 z = Vec2::ZERO;

    EXPECT_EQ( a, z );
}

TEST(Math, Vector2_Length)
{
    const Vec2 a( 1.0f, 2.0f );
    EXPECT_FLOAT_EQ( 2.23606798f, length( a ) );
}

TEST(Math, Vector2_LengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, length( TVector2<float>::ZERO ) );
}

TEST(Math, Vector2_SquaredLength)
{
    const Vec2 a( 1.0f, 2.0f );
    EXPECT_FLOAT_EQ( 5.0f, lengthSquared( a ) );
}

TEST(Math, Vector2_SquareLengthZero)
{
    EXPECT_FLOAT_EQ( 0.0f, lengthSquared( TVector2<float>::ZERO ) );
}

TEST(Math, Vector2_Normalization)
{
    const Vec2 a( 3.0f, 1.0f );
    const Vec2 n = normalized( a );

    EXPECT_TRUE(
            VectorEquals( 
                Vec2( 0.948683298f, 0.316227766f ),
                n )
    );
}

TEST(Math, Vector2_Lerp)
{
    const Vec2 a( 1.0f, 2.0f );
    const Vec2 b( 2.0f, 4.0f );

    EXPECT_TRUE( VectorEquals( Vec2( 1.0f, 2.0f ), lerp( a, b, 0.0f ) ) );
    EXPECT_TRUE( VectorEquals( Vec2( 1.5f, 3.0f ), lerp( a, b, 0.5f ) ) );
    EXPECT_TRUE( VectorEquals( Vec2( 2.0f, 4.0f ), lerp( a, b, 1.0f ) ) );
}

TEST(Math, Vector2_Min)
{
    const Vec2 a( 1.0f, 3.0f );
    const Vec2 b( 1.5f, 2.0f );

    EXPECT_TRUE( VectorEquals( Vec2( 1.0f, 2.0f ), min( a, b ) ) );
}

TEST(Math, Vector2_Max)
{
    const Vec2 a( 1.0f, 3.0f );
    const Vec2 b( 1.5f, 2.0f );

    EXPECT_TRUE( VectorEquals( Vec2( 1.5f, 3.0f ), max( a, b ) ) );
}

TEST(Math, Vector2_Clamp)
{
    const Vec2 a( 1.5f, 1.5f );
    const Vec2 min( 1.0f, 2.0f );
    const Vec2 max( 2.0f, 3.0f );

    EXPECT_TRUE( VectorEquals( Vec2( 1.5f, 2.0f ), clamp( a, min, max ) ) );
}
