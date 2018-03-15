#include "disconnectedgraphsearch.h"

DisconnectedGraphSearch::DisconnectedGraphSearch(const Graphe<EdgeData, VertexData>* graph, bool exploreComponents) :
        Search(graph) {
    _exploreComponents = exploreComponents;
}

void DisconnectedGraphSearch::reset() {
    _componentsCount = 0;
    Search::reset();
}

void DisconnectedGraphSearch::search(const Sommet<VertexData>* start) {
    if(start != nullptr) {
        _componentsCount++;
        Search::search(start);
        if(!_exploreComponents) {
            end();
            return;
        }
    }

    for(auto vertex = graph()->sommets(); vertex; vertex = vertex->next) {
        try {
            _vertexComponent.at(vertex->value);
        }
        catch (std::out_of_range& e) {
            _componentsCount++;
            Search::search(vertex->value);
            if(!_exploreComponents) {
                break;
            }
        }
    }

    end();
}

unsigned int DisconnectedGraphSearch::component(const Sommet<VertexData>* vertex) const {
    try {
        return _vertexComponent.at(vertex);
    }
    catch(std::out_of_range& e) {
        return 0;
    }
}

void DisconnectedGraphSearch::analyzeVertex(const Sommet<VertexData>* vertex) {
    _vertexComponent[vertex] = _componentsCount;
    analyzeVertex2(vertex);
}

void DisconnectedGraphSearch::end() {

}
