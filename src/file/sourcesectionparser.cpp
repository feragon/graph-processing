#include <iostream>
#include "sourcesectionparser.h"
#include "../util/string.h"

SourceSectionParser::SourceSectionParser(SectionParserCOR* next) :
        SectionParserCOR("source", next) {

}

bool SourceSectionParser::canParse(const std::string& line) const {
    return SectionParserCOR::canParse(line) || compareCaseInsensitive(line, "sources");
}

bool SourceSectionParser::parseInternal(const std::string& line) {
    if(canParse(line)) {
        return true;
    }

    if(line.empty()) {
        return false;
    }

    std::cout << "Source trouvée : " << line.substr(0, line.find(' ')) << std::endl;
}
