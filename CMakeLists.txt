cmake_minimum_required(VERSION 2.8)
project(smath)

include(CMake/GTest.cmake)

set( smath_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/angle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/constants.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/conversion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/interpolation.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/matrix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/perlin.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/matrixutils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/quaternion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/random.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/rect.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/tmatrix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/util.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/vector.h
)

set( smath_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/fastsqrt.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hashfloat.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/random.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/randomstate.cpp
)

set( smath_TESTS
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_angle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_conversions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_interpolation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_matrix4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_matrixutils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vector4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vector2.cpp
)

# Options
option( MATH_COMMON_TYPEDEFS  "Allow template types to predefine common types" on)
option( MATH_USE_FUZZY_EQUALS "Allow error delta when comparing floating point delta" on )
option( MATH_USE_DOUBLES      "Use double precision floats" off )
option( MATH_DEBUG_MODE       "Enable assertions in math calculations (slow)" on )
option( MATH_INTRINSICS_VS    "Enable SSE optimizations using MSVS intrinsics" off)
option( MATH_STATIC_LIBRARY   "Build smath as a static library" on)
option( MATH_UNIT_TESTS       "Build smath unit tests" on)

# set up math config
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/config.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/src/smath/config.h )

# package information
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "smath")
set(CPACK_PACKAGE_VENDOR "Scott MacDonald")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple 2D and 3D math library, designed for game development.")
set(CPACK_PACKAGE_VERSION "0.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "smath")

set(CPACK_RPM_PACKAGE_NAME "smath-devel")
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_LICENCE "Simplified BSD")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_DESCRIPTION "
smath is a 2D and 3D light weight math library written using modern C++ techniques. It is designed to be easy to use, understand, and fully unit tested.
It includes 2D/3D/4D vectors, 3D/4D matrices, rotations, interpolations, random values and other math utilities.")

#============================================================================
# Build configuration
#============================================================================
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	set(CMAKE_CXX_FLAGS                "-Wall -Wextra -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
    endif ()
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS                "-Wall -Wextra -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
elseif( MSVC11 )
	# Workaround for the fact that vc++ does not support vardic templates (yet)
	add_definitions(/D_VARIADIC_MAX=10)

	# Libcommon flags and other global flags
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNDEBUG=1=1 /D_DEBUG=1 /DUNICODE /D_UNICODE")

	# Enable security checks
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gs")

	# Disable several level 4 warnings about ansi compliance
	# (-wNNN)
	# - Not using Microsoft's 'secure' file functions
	# - Dead functions generated from glut
	# - Non-existant PDB files (we should probably fix this)
	# - Warning about nameless struct/union
	# - conditional expression is constant ( assert( x && "..." ) )
	# - unknown pragma
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996 /wd4505 /wd4099 /wd4201 /wd4127 /wd4068")

	# Misc options
	# J: Make visual studio treat chars as unsigned rather than signed
	# Zi: Generate PDB for debugging
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2 /nologo /J /Zi")
	
	# Defines specific for windows platform
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32_LEAN_AND_MEAN")
else()
    message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif()

# Static and dynamic library
if( MATH_STATIC_LIBRARY )
	message( "Building smath as a static library" )
    add_library( smath STATIC ${smath_SOURCES} ${smath_HEADERS} )
else()
	message( "Building smath as a dynamic library" )
    add_library( smath SHARED ${smath_SOURCES} ${smath_HEADERS} )
endif()

set_target_properties( smath PROPERTIES VERSION 0.1.0 )

# Unit tests
if( MATH_UNIT_TESTS )
    add_subdirectory( thirdparty/gtest )
    include_directories( thirdparty/gtest/src )
    enable_testing()
	
    if(MSVC)
        fix_default_compiler_settings_()
    endif()

	add_library( smath_unittest STATIC ${smath_SOURCES} ${smath_HEADERS} )

    add_gtest( test_angle smath_unittest )
    add_gtest( test_conversions smath_unittest )
    add_gtest( test_interpolation smath_unittest )
    add_gtest( test_matrix4 smath_unittest )
    add_gtest( test_matrixutils smath_unittest )
    add_gtest( test_quaternion smath_unittest )
    add_gtest( test_rect smath_unittest )
    add_gtest( test_utils smath_unittest )
    add_gtest( test_vector4 smath_unittest )
    add_gtest( test_vector3 smath_unittest )
    add_gtest( test_vector2 smath_unittest )
endif()

# Installation
if ( MATH_STATIC_LIBRARY )
    install( TARGETS  smath ARCHIVE DESTINATION lib )
else()
    install( TARGETS smath DESTINATION lib )
endif()
