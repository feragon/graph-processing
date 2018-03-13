#pragma once

#include <graph/graphe.h>
#include <unordered_map>
#include "search.h"

struct DFSVertexData {
    unsigned int unexploredNeighborsCount = 0;
    std::vector<const Sommet<VertexData>*> parents;
    unsigned int prefixNumber = 0;
    unsigned int suffixNumber = 0;
};

class DFS : public Search {
    public:
        DFS(const Graphe<EdgeData, VertexData>* graph, const Sommet<VertexData>* start);

        virtual void analyzeVertex(const Sommet<VertexData>* vertex) override;

        /**
         * @brief Donne le numéro de préfixe, commençant à 1
         * @return Préfixe
         */
        unsigned int prefixNumber(const Sommet<VertexData>* vertex) const;

        /**
         * @brief Donne le numéro de suffixe, commençant à 1
         * @return Suffixe
         */
        unsigned int suffixNumber(const Sommet<VertexData>* vertex) const;

        void search() override;

    private:
        /**
         * @brief Marque un voisin comme exploré et ferme les sommets nécessaires
         * @param neighbor Voisin
         */
        void neighborExplored(const Sommet<VertexData>* neighbor);

        unsigned int _nextPrefixNumber;
        unsigned int _nextSuffixNumber;
        std::unordered_map<const Sommet<VertexData>*, DFSVertexData> _vertexData;
};