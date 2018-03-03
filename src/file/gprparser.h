#pragma once

#include "../graph/graphe.h"
#include "sectionparsercor.h"

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

    private:
        GPRParser(const GPRParser&);

        std::istream& _buffer;
        SectionParserCOR* _parser;
};