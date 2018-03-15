#pragma once

#include "view.h"

class DOTGeneratorView : public View {
    public:
        DOTGeneratorView(std::ostream& out, std::istream& in, CLI* cli, DotMetaData* dmd);

        void show() override;

    private:
        DotMetaData* _dmd;
};