#pragma once

#include <ostream>
#include <modeling/modelinggraph.h>
#include "dotmetadata.h"

class DotWriter {
    public:
        DotWriter(std::ostream& out);

        void writeGraph(const std::string& name, const ModelingGraph& graph, DotMetaData metaData = DotMetaData());

    private:
        void writeEdges(const ModelingGraph& graph, DotMetaData metaData);
        void writeEdge(const Arete<EdgeData, VertexData>* edge, DotMetaData metaData);

        void writeVertices(const ModelingGraph& graph, DotMetaData metaData);
        void writeVertice(const Sommet<VertexData>* vertex, DotMetaData metaData);
        std::ostream& _out;
};;