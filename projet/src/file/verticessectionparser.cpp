#include <iostream>
#include "verticessectionparser.h"
#include "../util/string.h"
#include "gprparser.h"

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
        VertexData* data;
        if(pos == std::string::npos) {
            data = new VertexData();
        }
        else {
            unsigned long pos2 = line.find(' ', pos + 1);

            try {
                //Borne inf et sup
                //L'attente est possible ici
                //T_j <- Max {a_j, T_i + t_ij}
                int inf = std::stoi(line.substr(pos, pos2 - pos));
                int sup = std::stoi(line.substr(pos2));

                data = new VertexData(inf, sup);
            }
            catch (std::exception& e) {
                data = new VertexData();
                std::cerr << "Impossible de lire les coordonnées de " << std::endl;
            }
        }

        parser->graphe().creerSommet(line.substr(0, pos), *data);
        delete data;
        return true;
    }
}
