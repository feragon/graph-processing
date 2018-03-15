#include "dfs.h"

DFS::DFS(const Graphe<EdgeData, VertexData>* graph, bool exploreComponents) :
        DisconnectedGraphSearch(graph, exploreComponents) {

}

void DFS::reset() {
    _nextPrefixNumber = 1;
    _nextSuffixNumber = 1;
    _hasCycle = false;
    _topologicalOrderUpdated = false;
    DisconnectedGraphSearch::reset();
}

void DFS::begin(const Sommet<VertexData>* start) {
    reset();
    DisconnectedGraphSearch::search(start);
}

void DFS::analyzeVertex2(const Sommet<VertexData>* vertex) {
    _vertexData[vertex].prefixNumber = _nextPrefixNumber++;

    unsigned int openNeighborsCount = 0;

    auto successors = graph()->successeurs(vertex);
    for(auto l = successors; l; l = l->next) {
        if(l->value->fin() == vertex) {
            _hasCycle = true;
        }
        if (explored(l->value->fin())) {
            if(!closed(l->value->fin())) {
                _hasCycle = true;
            }
        }
        else {
            _vertexData[l->value->fin()].parents.push_back(vertex);
            openNeighborsCount++;

            nextEdges().insert(nextEdges().begin(), l->value);
        }
    }

    setExplored(vertex);

    if(openNeighborsCount == 0) {
        close(vertex);
    }

    _vertexData[vertex].openNeighborsCount = openNeighborsCount;

    Liste<Arete<EdgeData, VertexData>>::efface1(successors);
}

void DFS::close(const Sommet<VertexData>* neighbor) {
    std::vector<const Sommet<VertexData>*> parents;
    parents.push_back(neighbor);

    while(!parents.empty()) {
        const Sommet<VertexData>* parent = *(parents.begin());
        parents.erase(parents.begin());

        close(parent, parents);
    }
}

void DFS::close(const Sommet<VertexData>* neighbor, std::vector<const Sommet<VertexData>*>& parents) {
    setClosed(neighbor);
    _vertexData[neighbor].suffixNumber = _nextSuffixNumber++;

    for(const Sommet<VertexData>* parent : _vertexData[neighbor].parents) {
        if(closed(parent)) {
            continue;
        }

        if(--(_vertexData[parent].openNeighborsCount) == 0) {
            parents.push_back(parent);
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

void DFS::updateTopologicalOrder() {
    if(_topologicalOrderUpdated || _hasCycle) {
        return;
    }

    for(auto& pair : _vertexData) {
        pair.second.topologicalNumber = _nextSuffixNumber - pair.second.suffixNumber;
    }
}

void DFS::end() {
    DisconnectedGraphSearch::end();
    updateTopologicalOrder();
}

unsigned int DFS::topologicalNumber(const Sommet<VertexData>* vertex) const {
    try {
        return _vertexData.at(vertex).topologicalNumber;
    }
    catch (std::out_of_range& e) {
        return 0;
    }
}
