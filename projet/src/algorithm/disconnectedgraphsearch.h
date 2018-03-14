#pragma once

#include <graph/graphe.h>
#include "search.h"

class DisconnectedGraphSearch : public Search {
    public:
        DisconnectedGraphSearch(const Graphe<EdgeData, VertexData>* graph);

        /**
         * @param vertex Sommet
         * @return Numéro de composante du sommet
         */
        unsigned int component(const Sommet<VertexData>* vertex) const;

        /**
         * @brief Donne le nombre de composantes du graphe
         * @return Nombre de composantes
         */
        inline unsigned int componentsCount() const;

        void reset() override;

    protected:
        /**
         * @brief Redéfinition de la recherche
         * @param start Sommet de départ, ou nullptr pour partir de n'importe quel sommet
         */
        void search(const Sommet<VertexData>* start) override;

        void analyzeVertex(const Sommet<VertexData>* vertex) override;

        /**
         * @brief Analyse d'un sommet
         * @param vertex Sommet
         */
        virtual void analyzeVertex2(const Sommet<VertexData>* vertex) = 0;

        /**
         * @brief Marque la fin de la recherche
         */
        virtual void end();

    private:
        std::map<const Sommet<VertexData>*, unsigned int> _vertexComponent;
        unsigned int _componentsCount;
};

unsigned int DisconnectedGraphSearch::componentsCount() const {
    return _componentsCount;
}