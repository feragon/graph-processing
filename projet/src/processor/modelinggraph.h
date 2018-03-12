#pragma once

#include "vertexdata.h"
#include "edgedata.h"
#include "../graph/graphe.h"
#include <map>

class ModelingGraph : public Graphe<EdgeData, VertexData> {
    public:
        /**
         * @brief Donne un sommet à partir de son nom
         * @param name Nom du sommet
         * @return Sommet
         * @throw VertexNotFound si le sommet n'existe pas
         */
        Sommet<VertexData>* vertex(const std::string& name) const;

        Sommet<VertexData>* creerSommet(const std::string& cle, const VertexData& content) override;

    private:
        std::map<std::string, Sommet<VertexData>*> _vertexes;
};