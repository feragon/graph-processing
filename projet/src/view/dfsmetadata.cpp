#include <graph/arete.h>
#include <file/dotmetadata.h>
#include "dfsmetadata.h"
#include <algorithm>

DFSMetaData::DFSMetaData(const DFS* dfs) {
    _dfs = dfs;
}

std::string DFSMetaData::getEdgeLabel(const Arete <EdgeData, VertexData>* edge) {
    try {
        return std::to_string(_dfs->order().at(edge));
    }
    catch (std::out_of_range& e) {
        return "";
    }
}

std::string DFSMetaData::getVertexBackground(const Sommet<VertexData>* vertex) {
    if(_dfs->closed(vertex)) {
        return "green";
    }
    else {
        return "red";
    }
}

std::string DFSMetaData::getEdgeStyle(const Arete<EdgeData, VertexData>* edge) {
    try {
        _dfs->order().at(edge);
        return "filled";
    }
    catch (std::out_of_range& e) {
        return "dotted";
    }
}

std::string DFSMetaData::getEdgeColor(const Arete<EdgeData, VertexData>* edge) {
    return "black";
}

std::string DFSMetaData::getVertexLabel(const Sommet<VertexData>* vertex) {
    return DotMetaData::getVertexLabel(vertex) + " " +
           + "P:" + std::to_string(_dfs->prefixNumber(vertex)) + " - "
           + "S:" + std::to_string(_dfs->suffixNumber(vertex));
}

std::string DFSMetaData::additionalData() {
    if(_dfs->hasCycle()) {
        return "";
    }

    std::map<unsigned int, const Sommet<VertexData>*> _topologicalOrder;
    for(auto l = _dfs->graph()->sommets(); l; l = l->next) {
        _topologicalOrder[_dfs->topologicalNumber(l->value)] = l->value;
    }

    std::ostringstream oss;

    for(unsigned int i = 1; i <= _dfs->suffixNumberCount(); i++) {
        oss << "{" << std::endl;
        oss << "rank=\"same\"" << std::endl;
        oss << "T" << i << "[group=\"topologicalOrder\",shape=\"plaintext\",color=\"white\"]" << std::endl;

        try {
            oss << _topologicalOrder.at(i)->cle() << std::endl;
        }
        catch (std::out_of_range& e) {

        }

        oss << "}" << std::endl;
    }

    for(unsigned int i = 1; i < _dfs->suffixNumberCount(); i++) {
        oss << "T" << i << " -> T" << i+1 << std::endl;
    }

    return oss.str();
}
