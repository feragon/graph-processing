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
        parser->setPuits(parser->graphe().vertex(line.substr(0, line.find(' '))));
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
