#pragma once

#include <processor/vertexdata.h>
#include <processor/edgedata.h>
#include <graph/arete.h>
#include <vector>

class Search {
    public:
        Search(const Graphe<EdgeData, VertexData>* graph, const Sommet<VertexData>* start);

        /**
         * @brief Commence le parcours
         */
        void search();

        /**
         * @brief Traite un sommet
         * @param vertex Sommet
         */
        virtual void analyzeVertex(const Sommet<VertexData>* vertex) = 0;

        /**
         * @return Ordre de parcours des arêtes
         */
        inline const std::vector<const Arete<EdgeData, VertexData>*>& order() const;

        /**
         * @return Graphe parcouru
         */
        inline const Graphe<EdgeData, VertexData>* graph() const;

        /**
         * @return Sommet de départ
         */
        inline const Sommet<VertexData>* start() const;

    private:
        /**
         * @brief Ajoute une arête à la liste du parcours
         * @param edge Arête parcourue
         */
        inline void addEdge(const Arete<EdgeData, VertexData>* edge);

        std::vector<const Arete<EdgeData, VertexData>*> _order;
        const Graphe<EdgeData, VertexData>* _graph;
        const Sommet<VertexData>* _start;
};

const std::vector<const Arete<EdgeData, VertexData>*>& Search::order() const {
    return _order;
}

void Search::addEdge(const Arete<EdgeData, VertexData>* edge) {
    _order.push_back(edge);
}

const Graphe<EdgeData, VertexData>* Search::graph() const {
    return _graph;
}

const Sommet<VertexData>* Search::start() const {
    return _start;
}
