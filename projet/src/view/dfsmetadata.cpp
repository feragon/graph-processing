#include <graph/arete.h>
#include <file/dotmetadata.h>
#include "dfsmetadata.h"

DFSMetaData::DFSMetaData(const DFS* dfs) {
    _dfs = dfs;
}

std::string DFSMetaData::getEdgeLabel(const Arete <EdgeData, VertexData>* edge) {
    return DotMetaData::getEdgeLabel(edge);
}
