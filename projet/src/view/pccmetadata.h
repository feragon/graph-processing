#pragma once

#include <file/dotmetadata.h>
#include <algorithm/pcc.h>

template <class PPCType>
class PCCMetaData : public DotMetaData {
    public:
        PCCMetaData(const PPCType* pcc, std::vector<const Sommet<VertexData>*> chemin);

        virtual std::string getEdgeLabel(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexBackground(const Sommet<VertexData>* vertex) override;

        virtual std::string getEdgeStyle(const Arete<EdgeData, VertexData>* edge) override;

        std::string getVertexLabel(const Sommet<VertexData>* vertex) override;

        std::map<std::string, std::vector<Sommet<VertexData>*>>
        getVerticesCluster(Liste<Sommet<VertexData>>* vertices) override;

    private:
        const PPCType* _pcc;
        std::vector<const Sommet<VertexData>*> _chemin;
};

template <class PPCType>
PCCMetaData<PPCType>::PCCMetaData(const PPCType *pcc, std::vector<const Sommet<VertexData>*> chemin) {
        _pcc = pcc;
        _chemin = chemin;
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getEdgeLabel(const Arete<EdgeData, VertexData> *edge) {
        unsigned long m = _chemin.size();

        if(_chemin.empty()) {
                return "";
        }

        for(unsigned int i = 0; i < m - 1; i++) {
                if(_chemin[i] == edge->debut() && _chemin[i+1] == edge->fin()) {
                        return DotMetaData::getEdgeLabel(edge);
                }
        }
        return "";
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getVertexBackground(const Sommet<VertexData> *vertex) {
        for(auto s : _chemin) {
                if(s == vertex)
                        return "green";
        }
        return DotMetaData::getVertexBackground(vertex);
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getEdgeStyle(const Arete<EdgeData, VertexData> *edge) {
        unsigned long m = _chemin.size();
        if(m < 2)
                return "dotted";
        else {
                for(unsigned long i = 0; i < m-1; i++) {
                        if(edge->debut() == _chemin[i] && edge->fin() == _chemin[i+1])
                                return "filled";
                }
        }

        return "dotted";
}

template <class PPCType>
std::string PCCMetaData<PPCType>::getVertexLabel(const Sommet<VertexData> *vertex) {
        return DotMetaData::getVertexLabel(vertex);
}

template <class PPCType>
std::map<std::string, std::vector<Sommet<VertexData> *>>
PCCMetaData<PPCType>::getVerticesCluster(Liste<Sommet<VertexData>> *vertices) {
        return DotMetaData::getVerticesCluster(vertices);
}
