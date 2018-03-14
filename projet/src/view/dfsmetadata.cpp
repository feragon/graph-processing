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
    else if(_dfs->explored(vertex)) { //TODO: utile ?
        return "blue";
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

std::string DFSMetaData::getVertexLabel(const Sommet<VertexData>* vertex) {
    return DotMetaData::getVertexLabel(vertex) + " " +
           + "P:" + std::to_string(_dfs->prefixNumber(vertex)) + " - "
           + "S:" + std::to_string(_dfs->suffixNumber(vertex));
}

std::map<std::string, std::vector<Sommet<VertexData>*>> DFSMetaData::getVerticesCluster(Liste<Sommet<VertexData>>* vertices) {
    std::map<std::string, std::vector<Sommet<VertexData>*>> res;

    for(auto vertex = vertices; vertex; vertex = vertex->next) {
        std::string cluster = "Composante " + std::to_string(_dfs->component(vertex->value));
        res[cluster].push_back(vertex->value);
    }

    return res;
}
