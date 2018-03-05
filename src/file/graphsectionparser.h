#pragma once

#include "sectionparsercor.h"

class GraphSectionParser : public SectionParserCOR {
    public:
        GraphSectionParser(SectionParserCOR* next);

        virtual bool canParse(const std::string& line) const override;

        virtual bool parseInternal(const std::string& line, GPRParser* parser) override;
};