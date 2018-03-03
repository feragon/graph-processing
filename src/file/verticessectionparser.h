#pragma once

#include "sectionparsercor.h"

class VerticesSectionParser : public SectionParserCOR {
    public:
        VerticesSectionParser(SectionParserCOR* next);

        virtual bool parseInternal(const std::string& line) override;
};