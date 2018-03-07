#include "modelinggraph.h"
#include "vertexnotfound.h"

Sommet<VertexData>* ModelingGraph::creerSommet(const std::string& cle, const VertexData& content) {
    Sommet<VertexData>* vertex = Graphe::creerSommet(cle, content);
    _vertexes[cle] = vertex;
    return vertex;
}

Sommet<VertexData>* ModelingGraph::vertex(const std::string& name) const {
    try {
        return _vertexes.at(name);
    }
    catch (std::out_of_range& e) {
        throw VertexNotFound(("Le sommet " + name + " n'a pas été trouvé.").c_str());
    }
}
