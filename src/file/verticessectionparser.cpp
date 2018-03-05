#include <iostream>
#include "verticessectionparser.h"
#include "../util/string.h"

VerticesSectionParser::VerticesSectionParser(SectionParserCOR* next) :
        SectionParserCOR("sectionSommets", next) {

}

bool VerticesSectionParser::parseInternal(const std::string& line, GPRParser* parser) {
    if(line.empty()) {
        return false;
    }

    if(compareCaseInsensitive(line, "sectionSommets")) {
        return true;
    }
    else {
        unsigned long pos = line.find(' ');
        if(pos == std::string::npos) {
            std::cout << "Sommet " << line << " trouvé" << std::endl;
        }
        else {
            unsigned long pos2 = line.find(' ', pos + 1);
            std::string name = line.substr(0, pos);

            try {
                //Borne inf et sup
                //L'attente est possible ici
                //T_j <- Max {a_j, T_i + t_ij}
                int inf = std::stoi(line.substr(pos, pos2 - pos));
                int sup = std::stoi(line.substr(pos2));

                std::cout << "Sommet " << name << " trouvé (" << inf << ";" << sup << ")" << std::endl;
            }
            catch (std::exception& e) {
                std::cerr << "Impossible de lire les coordonnées de " << std::endl;
            }
        }
        return true;
    }
}
