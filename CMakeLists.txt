cmake_minimum_required(VERSION 3.6)
project(projet-modelisation)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(projet)
add_subdirectory(tests)