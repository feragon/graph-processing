#pragma once

#include "sectionparsercor.h"

class PuitsSectionParser : public SectionParserCOR {
    public:
        PuitsSectionParser(SectionParserCOR* next);

        virtual bool parseInternal(const std::string& line, GPRParser* parser) override;
};