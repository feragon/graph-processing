#include "dotmetadata.h"

std::string DotMetaData::getEdgeLabel(const Arete<EdgeData, VertexData>* edge) {
    std::ostringstream oss;
    oss << "[" << edge->contenu().cost() << ";" << edge->contenu().time() << "]";
    return oss.str();
}

std::string DotMetaData::getVertexBackground(const Sommet<VertexData>* vertex) {
    return "white";
}

std::string DotMetaData::getEdgeStyle(const Arete<EdgeData, VertexData>* edge) {
    return "filled";
}
