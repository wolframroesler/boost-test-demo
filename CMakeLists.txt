# Boost::test demonstration
# by Wolfram Rösler 2018-09-29

# Require a recent cmake version
cmake_minimum_required(VERSION 3.5)

# Activate C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Activate the boost::test package
set (CMAKE_FIND_LIBRARY_PREFIXES lib)
set (Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Our own include directory
include_directories(include)

# Our library
project(mylib)
add_library(mylib STATIC
    lib/base64.cpp
)

# The example application
project(myapp)
add_executable(myapp
    app/main.cpp
)
target_link_libraries(myapp
    mylib
)

# The test program
project(mytest)
add_executable(mytest
    test/main.cpp
    test/base64.cpp
    test/datadriven.cpp
)
target_link_libraries(mytest
    mylib
    ${Boost_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

# Activate "make test" (aka ctest)
enable_testing()
add_test(NAME mytest COMMAND mytest --random --log_level=test_suite)
