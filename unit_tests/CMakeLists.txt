add_library( ut_core )
target_sources( ut_core PRIVATE unit_test_core.cc )
target_link_libraries( ut_core
  PUBLIC
    small_vectors
    #Boost::unit_test_framework Boost::system
    Boost::ut
    )
target_include_directories( ut_core PUBLIC ut_core )
target_compile_options(ut_core
  PUBLIC
    ${SMALL_VECTORS_COMPILE_OPTIONS}
    )
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(ut_core
    PUBLIC
      -Wno-disabled-macro-expansion
      -Wno-used-but-marked-unused
      -Wno-global-constructors
      -Wno-exit-time-destructors
      -Wno-ctad-maybe-unsupported
      )
endif()

function( add_unittest name )
  add_executable(${name})
  target_sources(${name} PRIVATE ${name}.cc)
  target_link_libraries( ${name} PRIVATE ut_core )

  add_dependencies(unit_tests ${name} )
  add_test( NAME ${name}_test COMMAND ${name} )
endfunction()

add_unittest(unaligned_ut)
target_compile_options(unaligned_ut PRIVATE -Wno-float-equal)

add_unittest(uninitialized_constexpr_ut)
add_unittest(static_vector_ut)
target_compile_options(static_vector_ut PRIVATE -Wno-float-equal)

add_unittest(small_vector_ut)
add_unittest(composed_pointer_with_data_ut)
add_unittest(meta_packed_struct_ut)
