#pragma once

#include <modeling/vertexdata.h>
#include <modeling/edgedata.h>
#include <graph/arete.h>
#include <vector>
#include <set>
#include <map>

/**
 * @brief Classe qui représente un parcours
 * L'historique des arêtes et les prochains sommets à traiter sont stockés ici
 */
class Search {
    public:
        /**
         * @param graph Graphe à parcourir
         */
        Search(const Graphe<EdgeData, VertexData>* graph);

        /**
         * @return Ordre de parcours des arêtes
         */
        inline const std::map<const Arete<EdgeData, VertexData>*, unsigned int>& order() const;

        /**
         * @return Graphe parcouru
         */
        inline const Graphe<EdgeData, VertexData>* graph() const;

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

        /**
         * @brief Remet a zéro l'instance
         */
        virtual void reset();

    protected:
        /**
         * @brief Traite un sommet
         * @param vertex Sommet
         */
        virtual void analyzeVertex(const Sommet<VertexData>* vertex) = 0;

        /**
         * @brief Commence le parcours
         * @param start Sommet de départ
         */
        virtual void search(const Sommet<VertexData>* start);

        /**
         * @return Liste des prochains sommets
         */
        inline std::vector<std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>>& nextVertices();

    private:
        unsigned int _nextEdgeNumber;
        std::set<const Sommet<VertexData>*> _explored;
        std::set<const Sommet<VertexData>*> _closed;

        std::map<const Arete<EdgeData, VertexData>*, unsigned int> _order;
        const Graphe<EdgeData, VertexData>* _graph;
        std::vector<std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>> _nextVertices;
};

const std::map<const Arete<EdgeData, VertexData>*, unsigned int>& Search::order() const {
    return _order;
}

const Graphe<EdgeData, VertexData>* Search::graph() const {
    return _graph;
}

std::vector<std::pair<const Sommet<VertexData>*, const Arete<EdgeData, VertexData>*>>& Search::nextVertices() {
    return _nextVertices;
}
