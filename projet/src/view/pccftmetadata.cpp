#include <graph/arete.h>
#include <file/dotmetadata.h>
#include "pccftmetadata.h"
#include <algorithm>

PCCFTMetaData::PCCFTMetaData(const PCCFT *pccft, std::vector<const Sommet<VertexData>*> chemin) {
    _pccft = pccft;
    _chemin = chemin;
}

std::string PCCFTMetaData::getEdgeLabel(const Arete<EdgeData, VertexData> *edge) {
    unsigned long m = _chemin.size();

    if(_chemin.empty()) {
        return "";
    }

    for(unsigned int i = 0; i < m - 1; i++) {
        if(_chemin[i] == edge->debut() && _chemin[i+1] == edge->fin()) {
            return DotMetaData::getEdgeLabel(edge);
        }
    }
    return "";
}

std::string PCCFTMetaData::getVertexBackground(const Sommet<VertexData> *vertex) {
    for(auto s : _chemin) {
        if(s == vertex)
            return "green";
    }
    return DotMetaData::getVertexBackground(vertex);
}

std::string PCCFTMetaData::getEdgeStyle(const Arete<EdgeData, VertexData> *edge) {
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

std::string PCCFTMetaData::getVertexLabel(const Sommet<VertexData> *vertex) {
    return DotMetaData::getVertexLabel(vertex);
}

std::map<std::string, std::vector<Sommet<VertexData> *>>
PCCFTMetaData::getVerticesCluster(Liste<Sommet<VertexData>> *vertices) {
    return DotMetaData::getVerticesCluster(vertices);
}
