# author  Zdenko Pavlik

cmake_minimum_required(VERSION 3.5)
project(basic_test)

enable_testing()

include_directories(..)
include_directories(../src)
include_directories(test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
set (SOURCES
    EatingTestImpl.cpp
    DummyTest.cpp
)

set(HEADERS
)

add_executable(runUnitTests ${HEADERS} ${SOURCES})
# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest pthread -lgtest -lgmock gtest_main )
add_test( runUnitTests runUnitTests )


