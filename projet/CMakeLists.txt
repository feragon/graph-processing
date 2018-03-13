cmake_minimum_required(VERSION 3.0)
project(projet-modelisation)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

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
        src/file/sectionparsercor.cpp
        src/file/sectionparsercor.h
        src/file/parseexception.h
        src/file/resourcessectionparser.cpp
        src/file/resourcessectionparser.h
        src/util/string.cpp
        src/util/string.h
        src/file/verticessectionparser.cpp
        src/file/verticessectionparser.h
        src/file/sourcesectionparser.cpp
        src/file/sourcesectionparser.h
        src/file/puitssectionparser.cpp
        src/file/puitssectionparser.h
        src/file/arcssectionparser.cpp
        src/file/arcssectionparser.h
        src/file/graphsectionparser.cpp
        src/file/graphsectionparser.h
        src/modeling/vertexdata.h
        src/modeling/vertexdata.cpp
        src/modeling/edgedata.cpp
        src/modeling/edgedata.h
        src/modeling/modelinggraph.cpp
        src/modeling/modelinggraph.h
        src/modeling/vertexnotfound.h
        src/modeling/negativevaluation.h
        src/algorithm/dfs.cpp
        src/algorithm/dfs.h
        src/algorithm/search.h
        src/algorithm/search.cpp
        src/algorithm/pcc.cpp
        src/algorithm/pcc.h
        src/algorithm/pairPereValeur.cpp
        src/algorithm/pairPereValeur.h
        src/file/dotwriter.cpp
        src/file/dotwriter.h
        src/file/dotmetadata.cpp
        src/file/dotmetadata.h
        src/view/dfsmetadata.cpp)

add_executable(projet-modelisation ${SOURCE_FILES})
add_library(projet ${SOURCE_FILES} src/view/dfsmetadata.h)