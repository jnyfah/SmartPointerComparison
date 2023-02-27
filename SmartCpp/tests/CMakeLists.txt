# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(PointerTests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Google Test library
find_package(GTest REQUIRED)

# Define the source files for the tests
set(TEST_SOURCES
    UniquePtrTest.cpp
    SharedPtrTest.cpp
)

# Create the test executable
add_executable(PointerTests ${TEST_SOURCES})

# Link against the Google Test and SmartCpp libraries
target_link_libraries(PointerTests PRIVATE GTest::GTest GTest::Main SmartCpp)

# Add the tests to the CTest framework
include(GoogleTest)
gtest_add_tests(TARGET PointerTests)
