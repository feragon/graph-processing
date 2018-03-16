#include "sccmetadata.h"
#include <time.h>

SCCMetaData::SCCMetaData(const std::map<const Sommet<VertexData>*, unsigned int>& scc) {
    _scc = scc;
}

std::string SCCMetaData::getEdgeLabel(const Arete<EdgeData, VertexData>* edge) {
    return "";
}

std::string SCCMetaData::getVertexBackground(const Sommet<VertexData>* vertex) {
    try {
        return _colors.at(_scc[vertex]);
    }
    catch (std::out_of_range& e) {
        srand(time(NULL));
        char color[8];
        sprintf(color, "#%x%x%x", rand() % 256, rand() % 256, rand() % 256);
        std::string colorStr(color);
        _colors[_scc[vertex]] = colorStr;
        return colorStr;
    }
}

std::string SCCMetaData::getEdgeStyle(const Arete<EdgeData, VertexData>* edge) {
    if(_scc[edge->debut()] == _scc[edge->fin()]) {
        return "filled";
    }
    return "dotted";
}

std::string SCCMetaData::getVertexLabel(const Sommet<VertexData>* vertex) {
    return "";
}

std::map<std::string, std::vector<Sommet<VertexData>*>> SCCMetaData::getVerticesCluster(Liste<Sommet<VertexData>>* vertices) {
    std::map<std::string, std::vector<Sommet<VertexData>*>> res;

    for(auto vertex = vertices; vertex; vertex = vertex->next) {
        res["CFC " + std::to_string(_scc[vertex->value])].push_back(vertex->value);
    }

    return res;
}
