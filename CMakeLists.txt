cmake_minimum_required(VERSION 3.27)
project(BooleanFuncMinimizer)

set(CMAKE_CXX_STANDARD 17)

# Create the C++ executable
add_executable(BooleanFuncMinimizer
        src/main.cpp
        src/BooleanMinimizer.cpp
        src/strategies/QuineMcCluskeyStrategy.cpp
        # add other .cpp files as needed
)
