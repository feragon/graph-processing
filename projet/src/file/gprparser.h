#pragma once

#include "sectionparsercor.h"
#include <modeling/vertexdata.h>
#include <modeling/edgedata.h>
#include <modeling/modelinggraph.h>

class GPRParser {
    public:
        GPRParser(std::istream& buffer);
        virtual ~GPRParser();

        /**
         * @brief Charge le graphe
         */
        void load();

        /**
         * @brief Nettoie une ligne des commentaires et des espaces en double
         * @param line Ligne à nettoyer
         */
        static void cleanLine(std::string& line);

        inline ModelingGraph& graphe();

        /**
         * @return Source
         */
        inline Sommet<VertexData>* source() const;

        /**
         * @brief Change la source
         * @param source Nouvelle source
         */
        inline void setSource(Sommet<VertexData>* source);

        /**
         * @return Puits
         */
        inline Sommet<VertexData>* puits() const;

        /**
         * @brief Change le puits
         * @param puits Nouveau puits
         */
        inline void setPuits(Sommet<VertexData>* puits);

    private:
        GPRParser(const GPRParser&);

        std::istream& _buffer;
        SectionParserCOR* _parser;
        ModelingGraph _graphe;
        Sommet<VertexData>* _source;
        Sommet<VertexData>* _puits;
};

ModelingGraph& GPRParser::graphe() {
    return _graphe;
}

Sommet<VertexData>* GPRParser::source() const {
    return _source;
}

void GPRParser::setSource(Sommet<VertexData>* source) {
    _source = source;
}

Sommet<VertexData>* GPRParser::puits() const {
    return _puits;
}

void GPRParser::setPuits(Sommet<VertexData>* puits) {
    _puits = puits;
}