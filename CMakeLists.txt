cmake_minimum_required(VERSION 3.0)
project(projet-modelisation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    src/graph/arete.h
    src/graph/conteneur.h
    src/graph/graphe.h
    src/graph/identifiable.cpp
    src/graph/identifiable.h
    src/graph/liste.h
    src/graph/sommet.h
    src/file/gprparser.cpp
    src/file/gprparser.h
    src/main.cpp
    src/file/sectionparser.h
    src/file/sectionparser.cpp
)

add_executable(projet-modelisation ${SOURCE_FILES})