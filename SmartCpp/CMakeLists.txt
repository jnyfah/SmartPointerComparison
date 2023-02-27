# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SmartCpp VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source files for the library
set(LIB_SOURCES
    src/UniquePtr.cpp
    src/SharedPtr.cpp
    src/WeakPtr.cpp
)

# Create the shared library
add_library(SmartCpp SHARED ${LIB_SOURCES})

# Set the include directories for the library
target_include_directories(SmartCpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# -------------------- Fetch googletest content--------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_GetProperties(googletest)

if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
enable_testing()
add_subdirectory(tests)
