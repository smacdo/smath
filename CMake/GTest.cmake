# - Add tests using GoogleTest
#
# Usage:
#  add_gtest( name cpp_files... )
#
# Author:
#  Scott MacDonald <scott@whitespaceconsideredharmful.com>
#  Google Team
#####################################################################
macro(fix_default_compiler_settings_)
  if (MSVC)
    # For MSVC, CMake sets certain flags to defaults we want to override.
    # This replacement code is taken from sample in the CMake Wiki at
    # http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace.
    foreach (flag_var
             CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
             CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if (NOT BUILD_SHARED_LIBS AND NOT gtest_force_shared_crt)
        # When Google Test is built as a shared library, it should also use
        # shared runtime libraries.  Otherwise, it may end up with multiple
        # copies of runtime library data in different modules, resulting in
        # hard-to-find crashes. When it is built as a static library, it is
        # preferable to use CRT as static libraries, as we don't have to rely
        # on CRT DLLs being available. CMake always defaults to using shared
        # CRT libraries, so we override that default here.
        string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
      endif()

      # We prefer more strict warning checking for building Google Test.
      # Replaces /W3 with /W4 in defaults.
      string(REPLACE "/W3" "-W4" ${flag_var} "${${flag_var}}")
    endforeach()
  endif()
endmacro()

function(add_gtest_with_flags name cxx_flags libs)
    add_executable(${name} thirdparty/gtest/src/gtest_main.cc ${ARGN})
    if ( cxx_flags )
        set_target_properties(${name} PROPERTIES COMPILE_FLAGS "${cxx_flags} /MTd")
	else()
		set_target_properties(${name} PROPERTIES COMPILE_FLAGS "/MTd") 
	endif()
    foreach(lib "${libs}")
        target_link_libraries(${name} ${lib})
    endforeach()
    target_link_libraries(${name} gtest)
    add_test(${name} ${name})
endfunction()

function(add_gtest name libs)
    add_gtest_with_flags("${name}" "${cxx_default}" "${libs}" "tests/${name}.cpp" ${ARGVN})
endfunction()
