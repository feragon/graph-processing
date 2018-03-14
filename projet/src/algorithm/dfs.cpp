#include "dfs.h"

DFS::DFS(const Graphe<EdgeData, VertexData>* graph) :
        DisconnectedGraphSearch(graph) {

}

void DFS::reset() {
    _nextPrefixNumber = 1;
    _nextSuffixNumber = 1;
    _hasCycle = false;
    DisconnectedGraphSearch::reset();
}

void DFS::begin(const Sommet<VertexData>* start) {
    reset();
    DisconnectedGraphSearch::search(start);
}

void DFS::analyzeVertex2(const Sommet<VertexData>* vertex) {
    _vertexData[vertex].prefixNumber = _nextPrefixNumber++;

    unsigned int unexploredNeighborsCount = 0;
    unsigned int exploredNeighborsCount = 0;

    auto successors = graph()->successeurs(vertex);
    for(auto l = successors; l; l = l->next) {
        if(l->value->fin() == vertex) {
            _hasCycle = true;
        }
        if (explored(l->value->fin())) {
            exploredNeighborsCount++;
        }
        else {
            _vertexData[l->value->fin()].parents.push_back(vertex);
            unexploredNeighborsCount++;

            nextEdges().insert(nextEdges().begin(), l->value);
        }
    }

    if(unexploredNeighborsCount == 0) {
        _vertexData[vertex].suffixNumber = _nextSuffixNumber++;
        setClosed(vertex);
    }

    if(exploredNeighborsCount > 0) {
        _hasCycle = true;
    }

    neighborExplored(vertex);

    _vertexData[vertex].unexploredNeighborsCount = unexploredNeighborsCount;

    Liste<Arete<EdgeData, VertexData>>::efface1(successors);
}

void DFS::neighborExplored(const Sommet<VertexData>* neighbor) {
    setExplored(neighbor);

    for(const Sommet<VertexData>* parent : _vertexData[neighbor].parents) {
        if(closed(parent)) {
            continue;
        }

        if(--(_vertexData[parent].unexploredNeighborsCount) == 0) {
            _vertexData[parent].suffixNumber = _nextSuffixNumber++;
            setClosed(parent);
        }
    }
}

unsigned int DFS::prefixNumber(const Sommet<VertexData>* vertex) const {
    try {
        return _vertexData.at(vertex).prefixNumber;
    }
    catch (std::out_of_range& e) {
        return 0;
    }
}

unsigned int DFS::suffixNumber(const Sommet<VertexData>* vertex) const {
    try {
        return _vertexData.at(vertex).suffixNumber;
    }
    catch (std::out_of_range& e) {
        return 0;
    }
}
