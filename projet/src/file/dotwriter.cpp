#include <modeling/modelinggraph.h>
#include "dotwriter.h"

DotWriter::DotWriter(std::ostream& out) : _out(out) {

}

void DotWriter::writeGraph(const std::string& name, const ModelingGraph& graph, DotMetaData* metaData) {
    _out << "digraph " << name << " {" << std::endl;
    _out << "node [style=filled]" << std::endl;
    writeVertices(graph, metaData);
    writeEdges(graph, metaData);
    _out << metaData->additionalData();
    _out << "}" << std::endl;
}

void DotWriter::writeEdges(const ModelingGraph& graph, DotMetaData* metaData) {
    auto tmp = graph.aretes();

    for(auto edge = tmp; edge; edge = edge->next) {
        writeEdge(edge->value, metaData);
    }
}

void DotWriter::writeEdge(const Arete<EdgeData, VertexData>* edge, DotMetaData* metaData) {
    _out << edge->debut()->cle() << " -> " << edge->fin()->cle()
         << " [label=\"" << metaData->getEdgeLabel(edge) << "\","
         << "style=\"" << metaData->getEdgeStyle(edge) << "\"]"
         << std::endl;
}

void DotWriter::writeVertices(const ModelingGraph& graph, DotMetaData* metaData) {
    unsigned int i = 0;
    auto clusters = metaData->getVerticesCluster(graph.sommets());

    if(clusters.size() == 1) {
        for (auto vertex : clusters.begin()->second) {
            writeVertex(vertex, metaData);
        }
    }
    else {
        for (auto cluster : clusters) {
            _out << "subgraph cluster" << i << " {" << std::endl;
            _out << "color=blue" << std::endl;
            _out << "label=\"" << cluster.first << "\"" << std::endl;

            for (auto vertex : cluster.second) {
                writeVertex(vertex, metaData);
            }

            _out << "}" << std::endl;
            i++;
        }
    }
}

void DotWriter::writeVertex(const Sommet<VertexData>* vertex, DotMetaData* metaData) {
    _out << vertex->cle()
         << " [color=\"" << metaData->getVertexBackground(vertex) << "\","
         << "label=\"" << metaData->getVertexLabel(vertex) << "\""
         << "]" << std::endl;
}
