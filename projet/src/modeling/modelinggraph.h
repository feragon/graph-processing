#pragma once

#include "vertexdata.h"
#include "edgedata.h"
#include "../graph/graphe.h"
#include <map>

class ModelingGraph : public Graphe<EdgeData, VertexData> {
    public:
        ModelingGraph();
        ModelingGraph(const ModelingGraph& other);
        /**
         * @brief Donne un sommet à partir de son nom
         * @param name Nom du sommet
         * @return Sommet
         * @throw VertexNotFound si le sommet n'existe pas
         */
        Sommet<VertexData>* vertex(const std::string& name) const;

        virtual Sommet<VertexData>* creerSommet(const std::string& cle, const VertexData& content) override;

        /**
         * Transpose le graphe
         * Les sommets et arêtes ne seront pas les mêmes
         * @return Graphe transposé
         */
        ModelingGraph reverse() const;

    private:
        std::map<std::string, Sommet<VertexData>*> _vertexes;
};