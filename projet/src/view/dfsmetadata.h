#pragma once

#include <file/dotmetadata.h>
#include <algorithm/dfs.h>

class DFSMetaData : public DotMetaData {
    public:
        DFSMetaData(const DFS* dfs);

        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        std::map<std::string, std::vector<Sommet<VertexData>*>>
        getVerticesCluster(Liste<Sommet<VertexData>>* vertices) override;

    private:
        const DFS* _dfs;
};