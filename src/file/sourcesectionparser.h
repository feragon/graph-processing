#pragma once

#include "sectionparsercor.h"

class SourceSectionParser : public SectionParserCOR {
    public:
        SourceSectionParser(SectionParserCOR* next);

        virtual bool parseInternal(const std::string& line) override;

        virtual bool canParse(const std::string& line) const override;
};