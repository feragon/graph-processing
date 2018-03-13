#include <graph/graphe.h>
#include "search.h"
#include <utility>

Search::Search(const Graphe <EdgeData, VertexData>* graph, const Sommet<VertexData>* start) {
    _graph = graph;
    _start = start;
}

void Search::search() {
    _closed.empty();
    _explored.empty();
    _nextVertices.empty();

    _nextVertices.emplace_back(
            std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>(_start, nullptr)
    );

    while(!_nextVertices.empty()) {
        auto nextVertexIt = _nextVertices.begin();
        auto nextVertex = *nextVertexIt;
        _nextVertices.erase(nextVertexIt);

        if(nextVertex.second) {
            _order.push_back(nextVertex.second);
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
