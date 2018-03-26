#pragma once

#include <file/dotmetadata.h>
#include <algorithm/pcc.h>

template <class PPCType>
class PCCMetaData : public DotMetaData {
    public:
        PCCMetaData(std::vector<std::pair<const Sommet<VertexData>*, int>> chemin);

        std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        std::string getEdgeColor(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        std::map<std::string, std::vector<Sommet<VertexData>*>>
        getVerticesCluster(Liste<Sommet<VertexData>>* vertices) override;

    private:
        std::vector<std::pair<const Sommet<VertexData>*, int>> _chemin;
};

template <class PPCType>
PCCMetaData<PPCType>::PCCMetaData(std::vector<std::pair<const Sommet<VertexData>*, int>> chemin) {
        _chemin = chemin;
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getEdgeLabel(const Arete<EdgeData, VertexData> *edge) {
        long m = _chemin.size();

        for(int i = 0; i < m-1; i++) {
                if(_chemin[i].first == edge->debut() && _chemin[i+1].first == edge->fin()) {
                        return DotMetaData::getEdgeLabel(edge);
                }
        }
        return "";
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getVertexBackground(const Sommet<VertexData> *vertex) {
        for(auto s : _chemin) {
                if(s.first == vertex)
                        return "green";
        }
        return DotMetaData::getVertexBackground(vertex);
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getEdgeStyle(const Arete<EdgeData, VertexData> *edge) {
        return DotMetaData::getEdgeStyle(edge);
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getEdgeColor(const Arete<EdgeData, VertexData> *edge) {
    long m = _chemin.size();

    for(long i = 0; i < m-1; i++) {
        if(edge->debut() == _chemin[i].first && edge->fin() == _chemin[i+1].first)
            return "blue";
    }
    return DotMetaData::getEdgeColor(edge);
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getVertexLabel(const Sommet<VertexData> *vertex) {
        for(auto s : _chemin) {
                if(s.first == vertex)
                        return (vertex->cle() + " : val=" + std::to_string(s.second));
        }
        return DotMetaData::getVertexLabel(vertex);
}

template <class PPCType>
std::map<std::string, std::vector<Sommet<VertexData> *>>
PCCMetaData<PPCType>::getVerticesCluster(Liste<Sommet<VertexData>> *vertices) {
        return DotMetaData::getVerticesCluster(vertices);
}
