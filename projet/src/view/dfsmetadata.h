#pragma once

#include <file/dotmetadata.h>
#include <algorithm/dfs.h>

class DFSMetaData : public DotMetaData {
    public:
        DFSMetaData(const DFS* dfs);

        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        virtual std::string getEdgeColor(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        std::string additionalData() override;


    private:
        const DFS* _dfs;
};