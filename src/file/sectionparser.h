#pragma once

#include <string>

class SectionParser {
    public:
        SectionParser(const std::string& sectionName);
        /**
         * @brief Lit une ligne du fichier
         * @param line Ligne à lire, nettoyée des commentaires et des espaces en double
         * @return Vrai si la ligne a bien été traitée
         */
        virtual bool parse(std::string line) const = 0;

    private:
        std::string _sectionName;
};