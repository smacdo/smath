# - Add tests using GoogleTest
#
# Usage:
#  add_gtest( name cpp_files... )
#
# Author:
#  Scott MacDonald <scott@whitespaceconsideredharmful.com>
#  Google Team
#####################################################################
function(add_gtest_with_flags name cxx_flags libs)
    add_executable(${name} thirdparty/gtest/src/gtest_main.cc ${ARGN})
    if ( cxx_flags )
        set_target_properties(${name} PROPERTIES COMPILE_FLAGS "${cxx_flags}")
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
