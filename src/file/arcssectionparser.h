#pragma once

#include "sectionparsercor.h"

class ArcsSectionParser : public SectionParserCOR {
    public:
        ArcsSectionParser(SectionParserCOR* next);

        virtual bool parseInternal(const std::string& line) override;
};