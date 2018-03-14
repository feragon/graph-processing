#include <graph/graphe.h>
#include "search.h"
#include <utility>

Search::Search(const Graphe <EdgeData, VertexData>* graph) {
    _graph = graph;
    _nextEdgeNumber = 0;
}

void Search::search(const Sommet<VertexData>* start) {
    _nextVertices.emplace_back(
            std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>(start, nullptr)
    );

    while(!_nextVertices.empty()) {
        auto nextVertexIt = _nextVertices.begin();
        auto nextVertex = *nextVertexIt;
        _nextVertices.erase(nextVertexIt);

        if(closed(nextVertex.first) || explored(nextVertex.first)) {
            continue;
        }

        if(nextVertex.second) {
            _order.insert(std::pair<const Arete<EdgeData, VertexData>*, unsigned int>(nextVertex.second, _nextEdgeNumber));
            _nextEdgeNumber++;
        }

        analyzeVertex(nextVertex.first);
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
    _nextVertices.empty();
}
