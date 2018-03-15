#include <stdexcept>
#include <iostream>
#include "resourcessectionparser.h"
#include "../util/string.h"

ResourcesSectionParser::ResourcesSectionParser(SectionParserCOR* next) :
        SectionParserCOR("ressources", next) {

}

bool ResourcesSectionParser::parseInternal(const std::string& line, GPRParser* parser) {
    if(!compareCaseInsensitive(line.substr(0, 10), "ressources")) {
        return false;
    }

    try {
        std::cout << "Resources found: " << std::stoi(line.substr(11)) << std::endl;
        return true;
    }
    catch (std::exception& e) {
        return false;
    }
}

bool ResourcesSectionParser::canParse(const std::string& line) const {
    return compareCaseInsensitive(line.substr(0, 10), "ressources");
}
