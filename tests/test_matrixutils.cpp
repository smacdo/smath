/**
 * Unit tests for matrix utils
 * (template type=float)
 */
#include <gtest/gtest.h>
#include <smath/matrix.h>
#include <smath/matrixutils.h>

#ifndef MATH_TYPEDEFS
typedef TMatrix4<float> Mat4;
typedef TVector3<float> Vec3;
#endif

TEST(Math,Math_RotationAroundX)
{
    Mat4 m = Math::createRotationAroundX<float>( 45.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_RotationAroundY)
{
    Mat4 m = Math::createRotationAroundY<float>( 45.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_RotationAroundZ)
{
    Mat4 m = Math::createRotationAroundZ<float>( 45.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_RotationAroundAxis)
{
    Mat4 m = Math::createRotationAroundAxis(
                    TVector3<float>( 1.0f, 0.0f, 0.0f ),
                    45.0f );

    EXPECT_EQ( m, m );
}

TEST(Math,Math_Translation)
{
    Mat4 m = Math::createTranslation( 45.0f, 5.0f, -6.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_Scale)
{
    Mat4 m = Math::createScale( 4.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_LookAt)
{
    Mat4 m = Math::createLookAt( Vec3( 2.0f, 5.0f, -8.0f ),
                                 Vec3( 0.0f, 0.0f,  1.0f ),
                                 Vec3( 0.0f, 1.0f,  0.0f ) );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_CreateFrustum)
{
    Mat4 m = Math::createFrustum( 30.0f,
                                        55.0f,
                                        10.0f,
                                        75.0f,
                                        00.1f,
                                        736.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_CreateOrtho)
{
    Mat4 m = Math::createOrtho( 0.0f, 640.0f,
                                      480.0f, 0.0f,
                                      0.01f,
                                      100.0f );
    EXPECT_EQ( m, m );
}

TEST(Math,Math_CreateRowOrder)
{
    Mat4 m = Math::createRowOrder<float>();
    EXPECT_EQ( m, m );
}

TEST(Math,Math_CreateColOrder)
{
    Mat4 m = Math::createColOrder<float>();
    EXPECT_EQ( m, m );
}
