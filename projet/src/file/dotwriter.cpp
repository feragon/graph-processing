#include <modeling/modelinggraph.h>
#include "dotwriter.h"

DotWriter::DotWriter(std::ostream& out) : _out(out) {

}

void DotWriter::writeGraph(const std::string& name, const ModelingGraph& graph, DotMetaData* metaData) {
    _out << "graph " << name << " {" << std::endl;
    _out << "node [style=filled]" << std::endl;
    writeVertices(graph, metaData);
    writeEdges(graph, metaData);
    _out << "}" << std::endl;
}

void DotWriter::writeEdges(const ModelingGraph& graph, DotMetaData* metaData) {
    auto tmp = graph.aretes();

    for(auto edge = tmp; edge; edge = edge->next) {
        writeEdge(edge->value, metaData);
    }
}

void DotWriter::writeEdge(const Arete<EdgeData, VertexData>* edge, DotMetaData* metaData) {
    _out << edge->debut()->cle() << " -- " << edge->fin()->cle()
         << " [label=\"" << metaData->getEdgeLabel(edge) << "\"]" << std::endl;
}

void DotWriter::writeVertices(const ModelingGraph& graph, DotMetaData* metaData) {
    auto tmp = graph.sommets();

    for(auto vertex = tmp; vertex; vertex = vertex->next) {
        writeVertex(vertex->value, metaData);
    }
}

void DotWriter::writeVertex(const Sommet<VertexData>* vertex, DotMetaData* metaData) {
    _out << vertex->cle() << " [color=\"" << metaData->getVertexBackground(vertex) << "\"]" << std::endl;
}
