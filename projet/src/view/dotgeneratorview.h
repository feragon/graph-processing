#pragma once

#include "view.h"
#include <file/dotmetadata.h>

class DOTGeneratorView : public View {
    public:
        DOTGeneratorView(std::ostream& out, std::istream& in, CLI* cli, DotMetaData* dmd);

        void show() override;

    private:
        DotMetaData* _dmd;
};