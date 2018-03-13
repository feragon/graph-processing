#include "dfs.h"

DFS::DFS(const Graphe<EdgeData, VertexData>* graph, const Sommet<VertexData>* start) :
        Search(graph, start) {

}

void DFS::analyzeVertex(const Sommet<VertexData>* vertex) {
    if(closed(vertex)) {
        return;
    }

    auto neighbors = graph()->adjacences(vertex);

    for(auto l = neighbors; l; l = l->next) {
        if(!explored(l->value->first)) {
            nextVertices().insert(nextVertices().begin(), *(l->value));
        }
    }

    setExplored(vertex);
    setClosed(vertex);

    Liste<std::pair<Sommet<VertexData>*, Arete<EdgeData, VertexData>*>>::efface1(neighbors);
}
