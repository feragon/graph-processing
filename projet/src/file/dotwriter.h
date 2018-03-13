#pragma once

#include <ostream>
#include <modeling/modelinggraph.h>

class DotWriter {
    public:
        DotWriter(std::ostream& out);

        void writeGraph(const std::string& name, const ModelingGraph& graph);

    private:
        void writeEdges(const ModelingGraph& graph);
        void writeEdge(const Arete<EdgeData, VertexData>* edge);
        std::ostream& _out;
};;