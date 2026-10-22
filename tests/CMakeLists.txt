cmake_minimum_required(VERSION 3.20)

project(blackjack_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GTEST_DIR "googletest/googletest" CACHE PATH "gtest directory")
include(GoogleTest)
set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
add_subdirectory("googletest")

file(GLOB TEST_FILES "*.cpp")

add_executable(blackjack_test ${TEST_FILES} ${CMAKE_SOURCE_DIR}/src/singletons/deck.cpp)

target_include_directories(blackjack_test PRIVATE ${CMAKE_SOURCE_DIR}/incl)
target_link_libraries(blackjack_test PRIVATE gtest_main)

gtest_discover_tests(blackjack_test)