#include <gtest/gtest.h>
#include <smath/vector.h>
#include <smath/matrix.h>

using namespace testing;

// Credit for the AlmostEquals method:
//  http://randomascii.wordpress.com/2012/01/11/tricks-with-the-floating-point-format/
//  http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

bool AlmostEquals( float, float, float, int );

bool AlmostEquals( float a, float b )
{
    const float MAX_DIFF = 0.000001f;
    const int MAX_ULPS = 10;

    return AlmostEquals( a, b, MAX_DIFF, MAX_ULPS );
}

bool AlmostEquals( float a, float b, float maxDiff, int maxUlps )
{
    union FloatT
    {
        FloatT( float num )
            : f( num )
        {
        }

        bool negative() const
        {
            return ( i > 31 ) != 0;
        }

        int32_t i;
        float f;
    };

    // Check if the numbers are really close -- needed when comparing numbers
    // near zero.
    float absDiff = fabs( a - b );

    if ( absDiff <= maxDiff )
    {
        return true;
    }

    // Conert floating point values into a custom struct so that we can parse
    // out their fields
    FloatT uA( a );
    FloatT uB( b );

    // Different signs means they do not match
    if ( uA.negative() != uB.negative() )
    {
        return false;
    }

    // Find the difference in ULPs
    int ulpsDiff = std::abs( uA.i - uB.i );

    if ( ulpsDiff <= maxUlps )
    {
        return true;
    }
    
    return false;
}

::testing::AssertionResult VectorEquals( const TVector2<float>& expected,
                                         const TVector2<float>& actual )
{
    bool xe = AlmostEquals( expected[0], actual[0] );
    bool ye = AlmostEquals( expected[1], actual[1] );

    if ( xe && ye )
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure()
            << "Expected <"
            << expected[0] << ", "
            << expected[1] << ">\n"
            << "Actual <"
            << actual[0]   << ", "
            << actual[1]   << ">";
    }
}

::testing::AssertionResult VectorEquals( const TVector3<float>& expected,
                                         const TVector3<float>& actual )
{
    bool xe = AlmostEquals( expected[0], actual[0] );
    bool ye = AlmostEquals( expected[1], actual[1] );
    bool ze = AlmostEquals( expected[2], actual[2] );

    if ( xe && ye && ze )
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure()
            << "Expected <"
            << expected[0] << ", "
            << expected[1] << ", "
            << expected[2] << ">\n"
            << "Actual <"
            << actual[0]   << ", "
            << actual[1]   << ", "
            << actual[2]   << ">";
    }
}

::testing::AssertionResult VectorEquals( const TVector4<float>& expected,
                                         const TVector4<float>& actual )
{
    bool xe = AlmostEquals( expected[0], actual[0] );
    bool ye = AlmostEquals( expected[1], actual[1] );
    bool ze = AlmostEquals( expected[2], actual[2] );
    bool we = AlmostEquals( expected[3], actual[3] );

    if ( xe && ye && ze && we )
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure()
            << "Expected <"
            << expected[0] << ", "
            << expected[1] << ", "
            << expected[2] << ", "
            << expected[3] << ">\n"
            << "Actual <"
            << actual[0]   << ", "
            << actual[1]   << ", "
            << actual[2]   << ", "
            << actual[3]   << ">";
    }
}

template<typename T>
bool MatrixEquals( const TMatrix4<T>& a, const TMatrix4<T>& b )
{
    bool equals = true;

    // test equality on each value
    for ( unsigned int i = 0; i < TMatrix4<T>::NUM_VALUES; ++i )
    {
        if ( !AlmostEquals( a[i], b[i] ) )
        {
            equals = false;
            break;
        }
    }

    // did they equal?
    if ( equals )
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure()
            << "Expected: " << a << std::endl
            << "Actual: "   << b << std::endl;
    }
}
