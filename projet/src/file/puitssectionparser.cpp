#include <iostream>
#include "puitssectionparser.h"
#include "gprparser.h"

PuitsSectionParser::PuitsSectionParser(SectionParserCOR* next) :
        SectionParserCOR("puits", next) {

}

bool PuitsSectionParser::parseInternal(const std::string& line, GPRParser* parser) {
    if(canParse(line)) {
        return true;
    }

    if(line.empty()) {
        return false;
    }

    try {
        unsigned long pos = line.find(' ');
        VertexData* data;

        Sommet<VertexData>* puits = parser->graphe().vertex(line.substr(0, line.find(' ')));

        if(pos != std::string::npos) {
            unsigned long pos2 = line.find(' ', pos + 1);

            try {
                int inf = std::stoi(line.substr(pos, pos2 - pos));
                int sup = std::stoi(line.substr(pos2));

                puits->contenu().setCanWait(true);
                puits->contenu().setInf(inf);
                puits->contenu().setSup(sup);
            }
            catch (std::exception& e) {
                std::cerr << "Impossible de lire les coordonnées de " << std::endl;
            }
        }

        parser->setPuits(puits);
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
