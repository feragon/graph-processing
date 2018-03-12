cmake_minimum_required(VERSION 3.6)
project(projet-modelisation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
)

include_directories(catch)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../projet/src)

add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests projet)