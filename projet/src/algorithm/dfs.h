#pragma once

#include <graph/graphe.h>
#include <unordered_map>
#include <modeling/modelinggraph.h>
#include "search.h"
#include "disconnectedgraphsearch.h"

struct DFSVertexData {
    unsigned int openNeighborsCount = 0;
    std::vector<const Sommet<VertexData>*> parents;
    unsigned int prefixNumber = 0;
    unsigned int suffixNumber = 0;
    unsigned int topologicalNumber = 0;
};

class DFS : public DisconnectedGraphSearch {
    public:
        DFS(const Graphe<EdgeData, VertexData>* graph, bool exploreComponents = true);

        /**
         * @brief Cherche un chemin entre deux somets
         * @param graph Graphe
         * @param start Début
         * @param end Fin
         * @return Vrai si le chemin existe
         */
        static bool pathExists(const Graphe<EdgeData, VertexData>* graph,
                               const Sommet<VertexData>* start,
                               const Sommet<VertexData>* end);

        /**
         * @brief Donne les CFC du graphe
         * @param graph Graphe
         * @return CFC
         */
        static std::map<const Sommet<VertexData>*, unsigned int> stronglyConnectedComponents(const ModelingGraph* graph);

        virtual void analyzeVertex2(const Sommet<VertexData>* vertex) override;

        /**
         * @brief Donne le numéro de préfixe, commençant à 1
         * @param vertex Sommet
         * @return Préfixe
         */
        unsigned int prefixNumber(const Sommet<VertexData>* vertex) const;

        /**
         * @brief Donne le numéro de suffixe, commençant à 1
         * @param vertex Sommet
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

        /**
         * @brief Donne le numéro topologique du sommet, commençant à 1
         * @param vertex Sommet
         * @return Numéro topologique
         */
        unsigned int topologicalNumber(const Sommet<VertexData>* vertex) const;

        /**
         * @brief Donne le nombre de numérotations suffixes
         * @return Nombre de numérotations suffixes
         */
        inline unsigned int suffixNumberCount() const;

    private:
        /**
         * @brief Ferme un voisin et ferme les sommets parents
         * @param neighbor Voisin
         */
        void close(const Sommet<VertexData>* neighbor);

        /**
         * @brief Ferme un voisin et ajoute les sommets parents à une liste
         * @param neighbor Voisin
         * @param parents Liste des parents
         */
        void close(const Sommet<VertexData>* neighbor, std::vector<const Sommet<VertexData>*>& parents);

        /**
         * @brief Met à jour l'ordre topologique des sommets
         */
        void updateTopologicalOrder();

    protected:
        void end() override;

    private:

        bool _topologicalOrderUpdated;

        unsigned int _nextPrefixNumber;
        unsigned int _nextSuffixNumber;
        bool _hasCycle;
        std::unordered_map<const Sommet<VertexData>*, DFSVertexData> _vertexData;
};

bool DFS::hasCycle() const {
        return _hasCycle;
}

unsigned int DFS::suffixNumberCount() const {
        return _nextSuffixNumber - 1;
}