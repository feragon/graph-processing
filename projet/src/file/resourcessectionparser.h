#pragma once

#include "sectionparsercor.h"

class ResourcesSectionParser : public SectionParserCOR {
    public:
        ResourcesSectionParser(SectionParserCOR* next);

        virtual bool parseInternal(const std::string& line, GPRParser* parser) override;

        virtual bool canParse(const std::string& line) const override;
};