#include <modeling/modelinggraph.h>
#include "dotwriter.h"

DotWriter::DotWriter(std::ostream& out) : _out(out) {

}

void DotWriter::writeGraph(const std::string& name, const ModelingGraph& graph) {
    _out << "graph " << name << " {" << std::endl;
    writeEdges(graph);
    _out << "}" << std::endl;
}

void DotWriter::writeEdges(const ModelingGraph& graph) {
    auto tmp = graph.aretes();

    for(auto edge = tmp; edge; edge = edge->next) {
        writeEdge(edge->value);
    }
}

void DotWriter::writeEdge(const Arete<EdgeData, VertexData>* edge) {
    _out << edge->debut()->cle() << " -- " << edge->fin()->cle()
         << " [label=\"[" << edge->contenu().cost() << ";"
         << edge->contenu().time() << "]\"]" << std::endl;
}
