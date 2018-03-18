#include "dotmetadata.h"

std::string DotMetaData::getEdgeLabel(const Arete<EdgeData, VertexData>* edge) {
    std::ostringstream oss;
    oss << "[" << edge->contenu().cost() << ";" << edge->contenu().time() << "]";
    return oss.str();
}

std::string DotMetaData::getVertexBackground(const Sommet<VertexData>* vertex) {
    return "lightgray";
}

std::string DotMetaData::getEdgeStyle(const Arete<EdgeData, VertexData>* edge) {
    return "filled";
}

std::string DotMetaData::getVertexLabel(const Sommet<VertexData>* vertex) {
    return vertex->cle();
}

std::map<std::string, std::vector<Sommet<VertexData>*>> DotMetaData::getVerticesCluster(Liste<Sommet<VertexData>>* vertices) {
    std::map<std::string, std::vector<Sommet<VertexData>*>> res;
    for(auto vertex = vertices; vertex; vertex = vertex->next) {
        res["C0"].push_back(vertex->value);
    }

    return res;
}

std::string DotMetaData::additionalData() {
    return "";
}
