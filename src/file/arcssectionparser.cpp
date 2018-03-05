#include <iostream>
#include "arcssectionparser.h"
#include "parseexception.h"

ArcsSectionParser::ArcsSectionParser(SectionParserCOR* next) :
        SectionParserCOR("sectionArcs", next) {

}

bool ArcsSectionParser::parseInternal(const std::string& line, GPRParser* parser) {
    if(canParse(line)) {
        return true;
    }
    if(line.empty()) {
        return false;
    }

    unsigned long pos1 = line.find(' ');
    unsigned long pos2 = line.find(' ', pos1 + 1);
    unsigned long pos3 = line.find(' ', pos2 + 1);
    unsigned long pos4 = line.find(' ', pos3 + 1);

    if(pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos || pos4 == std::string::npos) {
        throw ParseException(("Ligne d'arc invalide : " + line).c_str());
    }

    std::string name = line.substr(0, pos1);
    std::string s1 = line.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string s2 = line.substr(pos2 + 1, pos3 - pos2 - 1);
    int cost;
    int time;

    try {
        cost = std::stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        time = std::stoi(line.substr(pos4 + 1));
    }
    catch(std::exception& e) {
        throw ParseException(("Ligne d'arc invalide : " + line).c_str());
    }

    std::cout << "Arc trouvé: " << name << " depuis " << s1 << " vers " << s2 << " cout " << cost << " temps " << time << std::endl;
    return true;
}
