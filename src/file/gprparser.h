#pragma once

#include "../graph/graphe.h"

class GPRParser {
    public:
        GPRParser(std::istream& buffer);

        /**
         * @brief Charge le graphe
         */
        void load();

    private:
        /**
         * @brief Nettoie une ligne des commentaires et des espaces en double
         * @param line Ligne à nettoyer
         */
        void cleanLine(std::string& line);

        std::istream& _buffer;
};