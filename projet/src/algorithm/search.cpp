#include <graph/graphe.h>
#include "search.h"
#include <utility>

Search::Search(const Graphe <EdgeData, VertexData>* graph) {
    _graph = graph;
    _nextEdgeNumber = 0;
}

void Search::search(const Sommet<VertexData>* start) {
    analyzeVertex(start);

    while(!_nextEdges.empty()) {
        auto nextEdgeIt = _nextEdges.begin();
        auto nextEdge = *nextEdgeIt;
        _nextEdges.erase(nextEdgeIt);

        if(closed(nextEdge->fin()) || explored(nextEdge->fin())) {
            continue;
        }

        _order.insert(std::pair<const Arete<EdgeData, VertexData>*, unsigned int>(nextEdge, _nextEdgeNumber));
        _nextEdgeNumber++;

        const Sommet<VertexData>* nextVertex = nextEdge->fin();
        analyzeVertex(nextVertex);
    }
}

bool Search::explored(const Sommet<VertexData>* vertex) const {
    return _explored.find(vertex) != _explored.end();
}

void Search::setExplored(const Sommet<VertexData>* vertex) {
    _explored.insert(vertex);
}

bool Search::closed(const Sommet<VertexData>* vertex) const {
    return _closed.find(vertex) != _closed.end();
}

void Search::setClosed(const Sommet<VertexData>* vertex) {
    _closed.insert(vertex);
}

void Search::reset() {
    _closed.empty();
    _explored.empty();
    _nextEdges.empty();
}
