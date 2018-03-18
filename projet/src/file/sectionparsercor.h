#pragma once

#include "sectionparser.h"

class SectionParserCOR : public SectionParser {
    public:
        SectionParserCOR(const std::string& sectionName, SectionParserCOR* next);
        virtual ~SectionParserCOR();

        virtual void parse(std::istream& is, GPRParser* parser) override;

        /**
         * @param line Permière ligne du bloc
         * @return Vrai si l'objet est capable de traiter le bloc
         */
        virtual bool canParse(const std::string& line) const;

        /**
         * @brief Traite une ligne du fichier
         * @param line Ligne
         * @return Faux si la ligne n'est pas reconnue
         */
        virtual bool parseInternal(const std::string& line, GPRParser* parser) = 0;

        /**
         * @brief Retourne le prochain expert
         * @return SectionParserCOR*
         */
        inline SectionParserCOR* next();

    private:
        SectionParserCOR* _next;
};

SectionParserCOR* SectionParserCOR::next() {
        return _next;
}