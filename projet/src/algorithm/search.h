#pragma once

#include <processor/vertexdata.h>
#include <processor/edgedata.h>
#include <graph/arete.h>
#include <vector>
#include <set>

/**
 * @brief Classe qui représente un parcours
 * L'historique des arêtes et les prochains sommets à traiter sont stockés ici
 */
class Search {
    public:
        /**
         * @param graph Graphe à parcourir
         * @param start Sommet de départ
         */
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

        /**
         * @param vertex Sommet
         * @return Vrai si le sommet a été exploré
         */
        bool explored(const Sommet<VertexData>* vertex) const;

        /**
         * @brief Marque le sommet comme exploré
         * @param vertex Sommet
         */
        void setExplored(const Sommet<VertexData>* vertex);

        /**
         * @param vertex Sommet
         * @return Vrai si le sommet a été fermé
         */
        bool closed(const Sommet<VertexData>* vertex) const;

        /**
         * @brief Ferme le sommet
         * @param vertex Sommet
         */
        void setClosed(const Sommet<VertexData>* vertex);

    protected:
        inline std::vector<std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>>& nextVertices();

    private:
        /**
         * @brief Ajoute une arête à la liste du parcours
         * @param edge Arête parcourue
         */
        inline void addEdge(const Arete<EdgeData, VertexData>* edge);

        std::set<const Sommet<VertexData>*> _explored;
        std::set<const Sommet<VertexData>*> _closed;

        std::vector<const Arete<EdgeData, VertexData>*> _order;
        const Graphe<EdgeData, VertexData>* _graph;
        const Sommet<VertexData>* _start;
        std::vector<std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>> _nextVertices;
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

std::vector<std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>>& Search::nextVertices() {
    return _nextVertices;
}
