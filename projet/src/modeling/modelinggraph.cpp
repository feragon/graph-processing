#include "modelinggraph.h"
#include "vertexnotfound.h"

ModelingGraph::ModelingGraph() {

}

ModelingGraph::ModelingGraph(const ModelingGraph& other) : Graphe<EdgeData, VertexData>(other) {
    for(auto l = sommets(); l; l = l->next) {
        _vertexes[l->value->cle()] = l->value;
    }
}

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

ModelingGraph ModelingGraph::reverse() const {
    ModelingGraph res;

    for(auto l = sommets(); l; l = l->next) {
        res.creerSommet(l->value->cle(), l->value->contenu());
    }

    for(auto l = aretes(); l; l = l->next) {
        res.creeArete(l->value->cle(), l->value->contenu(), res.vertex(l->value->fin()->cle()), res.vertex(l->value->debut()->cle()));
    }

    return res;
}
