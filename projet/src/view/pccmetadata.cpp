#include <graph/arete.h>
#include <file/dotmetadata.h>
#include "pccmetadata.h"
#include <algorithm>

PCCMetaData::PCCMetaData(const PCC *pcc, std::vector<const Sommet<VertexData>*> chemin) {
    _pcc = pcc;
    _chemin = chemin;
}

std::string PCCMetaData::getEdgeLabel(const Arete<EdgeData, VertexData> *edge) {
    return DotMetaData::getEdgeLabel(edge);
}

std::string PCCMetaData::getVertexBackground(const Sommet<VertexData> *vertex) {
    for(auto s : _chemin) {
        if(s == vertex)
            return "green";
    }
    return DotMetaData::getVertexBackground(vertex);
}

std::string PCCMetaData::getEdgeStyle(const Arete<EdgeData, VertexData> *edge) {
    unsigned long m = _chemin.size();
    if(m < 2)
        return "dotted";
    else {
        for(unsigned long i = 0; i < m-1; i++) {
            if(edge->debut() == _chemin[i] && edge->fin() == _chemin[i+1])
                return "filled";
        }
    }

    return "dotted";
}

std::string PCCMetaData::getVertexLabel(const Sommet<VertexData> *vertex) {
    return DotMetaData::getVertexLabel(vertex);
}

std::map<std::string, std::vector<Sommet<VertexData> *>>
PCCMetaData::getVerticesCluster(Liste<Sommet<VertexData>> *vertices) {
    return DotMetaData::getVerticesCluster(vertices);
}
