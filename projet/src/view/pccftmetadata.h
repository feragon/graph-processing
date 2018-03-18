#pragma once

#include <file/dotmetadata.h>
#include <algorithm/pccft.h>

class PCCFTMetaData : public DotMetaData {
    public:
        PCCFTMetaData(const PCCFT* pccft, std::vector<const Sommet<VertexData>*> chemin);

        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        std::map<std::string, std::vector<Sommet<VertexData>*>>
        getVerticesCluster(Liste<Sommet<VertexData>>* vertices) override;

    private:
        const PCCFT* _pccft;
        std::vector<const Sommet<VertexData>*> _chemin;
};
