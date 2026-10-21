cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_BINARY_DIR}>")

add_executable(blackjack ${SOURCES})
target_include_directories(blackjack PRIVATE ${PROJECT_SOURCE_DIR}/incl)

enable_testing()
add_subdirectory(tests)