#include <graph/arete.h>
#include <file/dotmetadata.h>
#include "dfsmetadata.h"

DFSMetaData::DFSMetaData(const DFS* dfs) {
    _dfs = dfs;
}

std::string DFSMetaData::getEdgeLabel(const Arete <EdgeData, VertexData>* edge) {
    return DotMetaData::getEdgeLabel(edge);
}

std::string DFSMetaData::getVertexBackground(const Sommet<VertexData>* vertex) {
    if(_dfs->closed(vertex)) {
        return "green";
    }
    else if(_dfs->explored(vertex)) { //TODO: utile ?
        return "blue";
    }
    else {
        return "red";
    }
}