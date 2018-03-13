#include "dfs.h"

DFS::DFS(const Graphe<EdgeData, VertexData>* graph, const Sommet<VertexData>* start) :
        Search(graph, start) {

}

void DFS::search() {
    _nextPrefixNumber = 1;
    _nextSuffixNumber = 1;

    Search::search();
}

void DFS::analyzeVertex(const Sommet<VertexData>* vertex) {
    if(closed(vertex) || explored(vertex)) {
        return;
    }

    _vertexData[vertex].prefixNumber = _nextPrefixNumber++;

    unsigned int unexploredNeighborsCount = 0;

    auto neighbors = graph()->adjacences(vertex);
    for(auto l = neighbors; l; l = l->next) {
        if(!explored(l->value->first)) {
            _vertexData[l->value->first].parents.push_back(vertex);
            unexploredNeighborsCount++;

            nextVertices().insert(nextVertices().begin(), *(l->value));
        }
    }

    if(unexploredNeighborsCount == 0) {
        _vertexData[vertex].suffixNumber = _nextSuffixNumber++;
        setClosed(vertex);
    }

    neighborExplored(vertex);

    _vertexData[vertex].unexploredNeighborsCount = unexploredNeighborsCount;

    Liste<std::pair<Sommet<VertexData>*, Arete<EdgeData, VertexData>*>>::efface1(neighbors);
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
