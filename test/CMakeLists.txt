
enable_testing()

find_package(GTest)

if(GTest_FOUND)
  # Test 1 simple Ellipsis test
  add_executable(SimpleEllipsisTest simple_ellipsis_test.cpp)

  target_link_libraries(SimpleEllipsisTest
                         GTest::gtest
                         GTest::gtest_main
                         curves)


  gtest_discover_tests(SimpleEllipsisTest SimpleEllipsisTest)
  if(lto_result)
    set_property(TARGET SimpleEllipsisTest PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

  # Test 2 simple Circle test
  add_executable(SimpleCircleTest simple_circle_test.cpp)

  target_link_libraries(SimpleCircleTest
                         GTest::gtest
                         GTest::gtest_main
                         curves)


  gtest_discover_tests(SimpleCircleTest SimpleCircleTest)
  if(lto_result)
    set_property(TARGET SimpleCircleTest PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
endif()
