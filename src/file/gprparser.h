#pragma once

#include "../graph/graphe.h"
#include "sectionparsercor.h"
#include "../processor/vertexdata.h"
#include "../processor/edgedata.h"

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

        inline Graphe<EdgeData, VertexData>& graphe();

    private:
        GPRParser(const GPRParser&);

        std::istream& _buffer;
        SectionParserCOR* _parser;
        Graphe<EdgeData, VertexData> _graphe;
};

Graphe<EdgeData, VertexData>& GPRParser::graphe() {
    return _graphe;
}
