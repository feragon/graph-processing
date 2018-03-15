#include <iostream>
#include "sourcesectionparser.h"
#include "../util/string.h"
#include "gprparser.h"

SourceSectionParser::SourceSectionParser(SectionParserCOR* next) :
        SectionParserCOR("source", next) {

}

bool SourceSectionParser::canParse(const std::string& line) const {
    return SectionParserCOR::canParse(line) || compareCaseInsensitive(line, "sources");
}

bool SourceSectionParser::parseInternal(const std::string& line, GPRParser* parser) {
    if(canParse(line)) {
        return true;
    }

    if(line.empty()) {
        return false;
    }

    try {
        parser->setSource(parser->graphe().vertex(line.substr(0, line.find(' '))));
        return true;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}
