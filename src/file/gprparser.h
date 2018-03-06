#pragma once

#include "sectionparsercor.h"
#include "../processor/vertexdata.h"
#include "../processor/edgedata.h"
#include "../processor/modelinggraph.h"

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

    private:
        GPRParser(const GPRParser&);

        std::istream& _buffer;
        SectionParserCOR* _parser;
        ModelingGraph _graphe;
};

ModelingGraph& GPRParser::graphe() {
    return _graphe;
}
