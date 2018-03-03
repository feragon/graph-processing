#pragma once

#include <string>

class SectionParser {
    public:
        SectionParser(const std::string& sectionName);
        /**
         * @brief Lit une ligne du fichier
         * @param is Buffer du fichier
         * @throw ParseException si une ligne n'a pas pu être traitée
         */
        virtual void parse(std::istream& is) = 0;

        /**
         * @return Nom de la section traitée
         */
        inline const std::string& sectionName() const;

    private:
        std::string _sectionName;
};

const std::string& SectionParser::sectionName() const {
        return _sectionName;
}
