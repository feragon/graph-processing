cmake_minimum_required(VERSION 3.6)
project(projet-modelisation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/testdfs.cpp
        src/testPCC.cpp
        src/testPCCParser.cpp
        src/testPCCArbreDeuxBranches.cpp
        src/testdfscycle.cpp
        src/testPCCFT.cpp src/testscc.cpp)

include_directories(catch)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../projet/src)

add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests projet)