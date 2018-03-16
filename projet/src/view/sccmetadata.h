#pragma once

#include <file/dotmetadata.h>

class SCCMetaData : public DotMetaData {
    public:
        SCCMetaData(const std::map<const Sommet<VertexData>*, unsigned int>& scc);

        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        virtual std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        virtual std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        virtual std::map<std::string, std::vector<Sommet<VertexData>*>> getVerticesCluster(Liste<Sommet<VertexData>>* vertices) override;

    private:
        std::map<const Sommet<VertexData>*, unsigned int> _scc;
        std::map<unsigned int, std::string> _colors;
};