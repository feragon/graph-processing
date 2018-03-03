#include <iostream>
#include "graphsectionparser.h"
#include "../util/string.h"
#include "parseexception.h"

GraphSectionParser::GraphSectionParser(SectionParserCOR* next) :
        SectionParserCOR("sectionGraphe", next) {

}

bool GraphSectionParser::canParse(const std::string& line) const {
    return SectionParserCOR::canParse(line) || compareCaseInsensitive(line, "sectionGraphes");
}

bool GraphSectionParser::parseInternal(const std::string& line) {
    if(canParse(line)) {
        return true;
    }

    if(line.empty()) {
        return true;
    }

    unsigned long pos2 = line.rfind(' ');
    unsigned long pos1 = line.rfind(' ', pos2 - 1);

    if(pos1 == std::string::npos || pos2 == std::string::npos) {
        throw ParseException(("Ligne de graphe invalide: " + line).c_str());
    }

    std::string name = line.substr(0, pos1);
    std::string source = line.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string puits = line.substr(pos2 + 1);
    std::cout << "Graphe trouvé: " << name << " source " << source << " puits " << puits << std::endl;
    return true;
}
