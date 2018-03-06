#include "modelinggraph.h"

Sommet<VertexData>* ModelingGraph::creerSommet(const std::string& cle, const VertexData& content) {
    Sommet<VertexData>* vertex = Graphe::creerSommet(cle, content);
    _vertexes[cle] = vertex;
    return vertex;
}

Sommet<VertexData>* ModelingGraph::vertex(const std::string& name) const {
    return _vertexes.at(name);
}
