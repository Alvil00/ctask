cmake_minimum_required(VERSION 3.30)
project(ctask LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
include(CheckIPOSupported)
check_ipo_supported(RESULT lto_result OUTPUT output LANGUAGES CXX)

find_package(OpenMP)

include_directories(include/)
add_compile_options(-Wall -Wpedantic)

if(NOT DEFINED CURVE_LIBRARY_TYPE)
  set(CURVE_LIBRARY_TYPE SHARED)
endif()
message(STATUS "Curves library make with ${CURVE_LIBRARY_TYPE} linkage")

add_library(curves ${CURVE_LIBRARY_TYPE} 
  ${CMAKE_SOURCE_DIR}/src/Ellipsis.cpp
  ${CMAKE_SOURCE_DIR}/src/Helix.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} curves)
if(OpenMP_FOUND)
  target_compile_definitions(${PROJECT_NAME} PUBLIC PARALELL )
  target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
endif()


if(lto_result)
  message(STATUS "IPO is supported")
  set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  set_property(TARGET curves PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(WARNING "IPO is not supported: ${output}")
endif()

add_subdirectory(test)



