#pragma once

#include <graph/graphe.h>
#include <unordered_map>
#include "search.h"
#include "disconnectedgraphsearch.h"

struct DFSVertexData {
    unsigned int unexploredNeighborsCount = 0;
    std::vector<const Sommet<VertexData>*> parents;
    unsigned int prefixNumber = 0;
    unsigned int suffixNumber = 0;
};

class DFS : public DisconnectedGraphSearch {
    public:
        DFS(const Graphe<EdgeData, VertexData>* graph);

        virtual void analyzeVertex2(const Sommet<VertexData>* vertex) override;

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

        /**
         * @brief Commence le parcours en profondeur
         * @param start Sommet de départ, ou nullptr pour commencer d'un sommet quelconque
         */
        void begin(const Sommet<VertexData>* start = nullptr);

        void reset() override;

        /**
         * @return Vrai si le graphe possède au moins un cycle
         */
        inline bool hasCycle() const;

    private:
        /**
         * @brief Marque un voisin comme exploré et ferme les sommets nécessaires
         * @param neighbor Voisin
         */
        void neighborExplored(const Sommet<VertexData>* neighbor);

        unsigned int _nextPrefixNumber;
        unsigned int _nextSuffixNumber;
        bool _hasCycle;
        std::unordered_map<const Sommet<VertexData>*, DFSVertexData> _vertexData;
};

bool DFS::hasCycle() const {
        return _hasCycle;
}
