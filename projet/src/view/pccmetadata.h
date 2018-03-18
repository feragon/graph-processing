#pragma once

#include <file/dotmetadata.h>
#include <algorithm/pcc.h>

class PCCMetaData : public DotMetaData {
    public:
        PCCMetaData(const PCC* pcc, std::vector<const Sommet<VertexData>*> chemin);

        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        std::map<std::string, std::vector<Sommet<VertexData>*>>
        getVerticesCluster(Liste<Sommet<VertexData>>* vertices) override;

    private:
        const PCC* _pcc;
        std::vector<const Sommet<VertexData>*> _chemin;
};
