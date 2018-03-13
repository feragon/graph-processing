#pragma once

#include <ostream>
#include <modeling/modelinggraph.h>
#include "dotmetadata.h"

class DotWriter {
    public:
        DotWriter(std::ostream& out);

        void writeGraph(const std::string& name, const ModelingGraph& graph, DotMetaData* metaData = nullptr);

    private:
        /**
         * @brief Écrit les arêtes sur la sortie
         * @param graph Graphe
         * @param metaData Données
         */
        void writeEdges(const ModelingGraph& graph, DotMetaData* metaData);

        /**
         * @brief Écrit une arête sur la sortie
         * @param edge Arête
         * @param metaData Données
         */
        void writeEdge(const Arete<EdgeData, VertexData>* edge, DotMetaData* metaData);

        /**
         * @brief Écrit les sommets sur la sortie
         * @param graph Graphe
         * @param metaData Données
         */
        void writeVertices(const ModelingGraph& graph, DotMetaData* metaData);

        /**
         * @brief Écrit un sommet sur la sortie
         * @param vertex Sommet
         * @param metaData Données
         */
        void writeVertex(const Sommet<VertexData>* vertex, DotMetaData* metaData);
        std::ostream& _out;
};;